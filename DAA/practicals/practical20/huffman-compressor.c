#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Max code length is usually max 256, but we set a safe buffer
#define MAX_CODE_LENGTH 256
#define MAX_CHARS 256
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.huff"

// --- Data Structures (Min-Heap and Tree) ---

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
char* huffmanCodes[MAX_CHARS] = {NULL};

// --- Utility Functions (Heap and Tree) ---

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

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

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

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to build the Huffman Tree (HUFFMAN_BUILD)
MinHeapNode* buildHuffmanTree(int* unique_chars_count) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createMinHeap(MAX_CHARS);
    *unique_chars_count = 0;

    for (int i = 0; i < MAX_CHARS; ++i) {
        if (charFreq[i] > 0) {
            minHeap->array[minHeap->size++] = newNode(i, charFreq[i]);
            (*unique_chars_count)++;
        }
    }
    buildMinHeap(minHeap);

    if (*unique_chars_count == 0) return NULL;
    if (*unique_chars_count == 1) {
         top = newNode(0, minHeap->array[0]->freq);
         top->left = minHeap->array[0];
         return top;
    }

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode(0, left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    MinHeapNode* root = extractMin(minHeap);
    free(minHeap);
    return root;
}

// Recursive function to store codes (HUFFMAN_ASSIGN_CODES)
void storeCodes(MinHeapNode* root, char* arr, int top) {
    if (root->left) {
        arr[top] = '0';
        storeCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = '1';
        storeCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        arr[top] = '\0';
        huffmanCodes[root->data] = (char*)malloc(top + 1);
        strcpy(huffmanCodes[root->data], arr);
    }
}

// Function to free the allocated memory for the tree
void freeTree(MinHeapNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// --- File I/O and Bit Manipulation ---

// Writes a single bit to the file using a buffer
void writeBit(FILE *fp, int bit, int *bit_count, unsigned char *buffer) {
    *buffer = (*buffer << 1) | (bit & 1);
    (*bit_count)++;

    if (*bit_count == 8) {
        fwrite(buffer, 1, 1, fp);
        *buffer = 0;
        *bit_count = 0;
    }
}

// Writes the remaining bits in the buffer, padding with zeros
void flushBits(FILE *fp, int *bit_count, unsigned char *buffer) {
    if (*bit_count > 0) {
        // Pad with zeros to complete the byte
        *buffer <<= (8 - *bit_count);
        fwrite(buffer, 1, 1, fp);
        *buffer = 0;
        *bit_count = 0;
    }
}

// Writes the frequency table (Header) to the file
void writeHeader(FILE *fp, int unique_chars_count) {
    // 1. Write the number of unique characters
    fwrite(&unique_chars_count, sizeof(int), 1, fp);

    // 2. Write the (char, frequency) pairs
    for (int i = 0; i < MAX_CHARS; i++) {
        if (charFreq[i] > 0) {
            unsigned char char_data = (unsigned char)i;
            long long freq_data = charFreq[i];

            // Write char
            fwrite(&char_data, sizeof(unsigned char), 1, fp);
            // Write frequency (using 8 bytes for safety)
            fwrite(&freq_data, sizeof(long long), 1, fp);
        }
    }
}

// --- Main Compression Logic ---

void compressFile(const char* input_filename, const char* output_filename) {
    // PASS 1: Calculate Frequencies
    FILE *fp_in = fopen(input_filename, "rb");
    if (!fp_in) {
        fprintf(stderr, "Error: Could not open input file %s\n", input_filename);
        return;
    }

    int c;
    long long total_chars = 0;
    while ((c = fgetc(fp_in)) != EOF) {
        charFreq[(unsigned char)c]++;
        total_chars++;
    }
    fclose(fp_in);

    // 2. Build Huffman Tree and Generate Codes
    int unique_chars_count = 0;
    MinHeapNode* root = buildHuffmanTree(&unique_chars_count);

    if (root == NULL || unique_chars_count == 0) {
        fprintf(stderr, "Error: Input file is empty.\n");
        return;
    }

    char arr[MAX_CODE_LENGTH];
    storeCodes(root, arr, 0);

    // 3. Write Compressed File (Header + Bitstream)
    FILE *fp_out = fopen(output_filename, "wb");
    if (!fp_out) {
        fprintf(stderr, "Error: Could not open output file %s\n", output_filename);
        freeTree(root);
        return;
    }

    // Write the Codebook (Header)
    writeHeader(fp_out, unique_chars_count);

    // PASS 2: Write Bitstream
    fp_in = fopen(input_filename, "rb");

    int bit_count = 0;
    unsigned char buffer = 0;
    long long compressed_bits = 0;

    while ((c = fgetc(fp_in)) != EOF) {
        char *code = huffmanCodes[(unsigned char)c];
        for (int i = 0; code[i] != '\0'; i++) {
            writeBit(fp_out, code[i] - '0', &bit_count, &buffer);
            compressed_bits++;
        }
    }

    // Flush any remaining bits in the buffer
    flushBits(fp_out, &bit_count, &buffer);

    fclose(fp_in);
    fclose(fp_out);

    printf("Compression Successful!\n");
    printf("Input File: %s (%lld bytes)\n", input_filename, total_chars);
    printf("Output File: %s (Unique Chars: %d)\n", output_filename, unique_chars_count);
    printf("Total Compressed Bits (excluding header): %lld\n", compressed_bits);

    // Cleanup
    for (int i = 0; i < MAX_CHARS; i++) {
        if (huffmanCodes[i] != NULL) free(huffmanCodes[i]);
    }
    freeTree(root);
}

int main(int argc, char *argv[]) {
    // For demonstration, we assume two files exist: input.txt and output.huff
    // In a real scenario, you'd check command line arguments.
    printf("--- Huffman Compressor ---\n");
    printf("NOTE: Using placeholder file names for demonstration:\n");
    printf("Input: %s, Output: %s\n\n", INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    // Create a dummy input file for testing
    FILE *dummy_in = fopen(INPUT_FILE_NAME, "w");
    if (dummy_in) {
        fprintf(dummy_in, "this is a test input for the huffman compression algorithm and decompression process.");
        fclose(dummy_in);
    }

    compressFile(INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    return 0;
}
