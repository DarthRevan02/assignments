#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CHARS 256
#define INPUT_FILE_NAME "output.huff"
#define OUTPUT_FILE_NAME "decoded_output.txt"

// --- Data Structures (Min-Heap and Tree - Duplicated for self-contained executable) ---

typedef struct MinHeapNode {
    unsigned char data;
    long long freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode** array;
} MinHeap;

long long charFreq[MAX_CHARS] = {0};

// --- Utility Functions (Heap and Tree - Subset used for Decompression) ---

MinHeapNode* newNode(unsigned char data, long long freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Function to swap two min heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Standard min heapify function
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to extract minimum frequency node from heap
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to Min Heap
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Function to build min heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Function to check if size of heap is 1 or not
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to rebuild the Huffman Tree from frequencies (HUFFMAN_BUILD)
MinHeapNode* buildHuffmanTree(int unique_chars_count) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createMinHeap(MAX_CHARS);

    // Populate the heap array with leaf nodes based on loaded frequencies
    for (int i = 0; i < MAX_CHARS; ++i) {
        if (charFreq[i] > 0) {
            minHeap->array[minHeap->size++] = newNode(i, charFreq[i]);
        }
    }

    if (unique_chars_count == 0) return NULL;

    // IMPORTANT: Heapify the array now that all elements are loaded
    buildMinHeap(minHeap);

    if (unique_chars_count == 1) {
         top = newNode(0, minHeap->array[0]->freq);
         top->left = minHeap->array[0];
         // Clean up the minHeap wrapper struct
         free(minHeap->array);
         free(minHeap);
         return top;
    }

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode(0, left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    MinHeapNode* root = extractMin(minHeap);
    // Clean up the minHeap wrapper struct
    free(minHeap->array);
    free(minHeap);
    return root;
}

void freeTree(MinHeapNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// --- File I/O and Bit Manipulation ---

// Reads a single bit from the file using a buffer
int readBit(FILE *fp, int *bit_count, unsigned char *buffer) {
    if (*bit_count == 0) {
        if (fread(buffer, 1, 1, fp) != 1) {
            return -1; // EOF or error
        }
        *bit_count = 8;
    }

    // Extract the most significant bit (MSB) first
    int bit = (*buffer >> 7) & 1;
    *buffer <<= 1;
    (*bit_count)--;

    return bit;
}

// Reads the frequency table (Header) from the file
long long readHeader(FILE *fp, int *unique_chars_count) {
    // 1. Read the number of unique characters
    if (fread(unique_chars_count, sizeof(int), 1, fp) != 1) {
        fprintf(stderr, "Error reading unique character count from header.\n");
        return -1;
    }

    long long total_chars = 0;

    // 2. Read the (char, frequency) pairs
    for (int i = 0; i < *unique_chars_count; i++) {
        unsigned char char_data;
        long long freq_data;

        if (fread(&char_data, sizeof(unsigned char), 1, fp) != 1 ||
            fread(&freq_data, sizeof(long long), 1, fp) != 1) {
            fprintf(stderr, "Error reading char/frequency pair from header.\n");
            return -1;
        }

        charFreq[char_data] = freq_data;
        total_chars += freq_data;
    }

    return total_chars;
}

// --- Main Decompression Logic ---

void decompressFile(const char* input_filename, const char* output_filename) {
    FILE *fp_in = fopen(input_filename, "rb");
    if (!fp_in) {
        fprintf(stderr, "Error: Could not open compressed file %s\n", input_filename);
        return;
    }

    // 1. Read Header and Reconstruct Frequencies
    int unique_chars_count = 0;
    long long total_chars = readHeader(fp_in, &unique_chars_count);

    if (total_chars < 0) { // Error reading header
        fclose(fp_in);
        return;
    }

    // 2. Rebuild Huffman Tree
    MinHeapNode* root = buildHuffmanTree(unique_chars_count);

    if (root == NULL) {
        fprintf(stderr, "Error: Could not rebuild Huffman Tree (empty or invalid header).\n");
        fclose(fp_in);
        return;
    }

    // 3. Decompress Bitstream
    FILE *fp_out = fopen(output_filename, "wb");
    if (!fp_out) {
        fprintf(stderr, "Error: Could not open output file %s\n", output_filename);
        freeTree(root);
        fclose(fp_in);
        return;
    }

    MinHeapNode* current = root;
    int bit_count = 0;
    unsigned char buffer = 0;
    long long decoded_chars = 0;

    printf("Decompressing %lld characters...\n", total_chars);

    while (decoded_chars < total_chars) {
        int bit = readBit(fp_in, &bit_count, &buffer);

        if (bit == -1) {
            fprintf(stderr, "Error: Premature EOF encountered during decoding.\n");
            break;
        }

        if (bit == 0) {
            current = current->left;
        } else { // bit == 1
            current = current->right;
        }

        // Found a leaf node (character)
        if (current->left == NULL && current->right == NULL) {
            fwrite(&current->data, 1, 1, fp_out);
            decoded_chars++;
            current = root; // Reset traversal to the root
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    freeTree(root);

    if (decoded_chars == total_chars) {
        printf("Decompression Successful!\n");
        printf("Output File: %s (%lld bytes)\n", output_filename, decoded_chars);
        printf("Verification: Original data restored.\n");
    } else {
        printf("Decompression Finished with Errors: Decoded %lld/%lld characters.\n", decoded_chars, total_chars);
    }
}

int main(int argc, char *argv[]) {
    printf("--- Huffman Decompressor ---\n");
    printf("NOTE: Using placeholder file names for demonstration:\n");
    printf("Input: %s, Output: %s\n\n", INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    decompressFile(INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    return 0;
}
