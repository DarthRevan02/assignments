#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #define MKDIR(path) mkdir(path, 0755)
#endif
#include "cpuTimer.h"

#define FILES_PER_SIZE 30
// gcc main.c experiment.c intSort.c miscfn.c cpuTimer.c -lm -O2 -o analyze
// gcc main.c intSort.c cpuTimer.c miscfn.c -lm -O2 -o analyze

int main()
{
    // Array of specifies sizes
    int sizes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 30000, 50000, 100000, 250000};
    int countIndex = sizeof(sizes) / sizeof(sizes[0]);
    // Seed the random number generator with the current time
    // This ensures that a different sequence of random numbers is generated each time the program runs.
    srand((unsigned int)time(NULL));
    double sTime = 0, eTime = sTime; // Initialize times
    sTime = getCpuTime();
    // Outer lpp:iterate through each size in the array
    for (int i = 0; i < countIndex; ++i)
    {
        int current_size =sizes[i];
        char foldername[100];
        sprintf(foldername, "SIZE_%07d", current_size);
        MKDIR(foldername); // Create directory for the current size
        //Inner loop:generate 30 files for the current size
        for(int j=1;j<=FILES_PER_SIZE;++j){
            char filename[50];
            FILE *file_ptr;
            //Generate the filename string using sprintf with padding:
            // - foldername is the directory name
            //- %07d pads the size to 7 digits with leading zeroes
            // - %02d pads the index to 2 digits with leading zeroes
            sprintf(filename, "%s/RANDOM_%07d_%02d.dat", foldername, current_size, j);
            // Open the file in write mode ("w")
            file_ptr = fopen(filename,"w");
             
            //Check if the file was opened successfully
            if(file_ptr == NULL){
                fprintf(stderr,"Error: Could not open file %s for writing.""Skipping.\n",filename);
                continue; //Skip to the next file
            } 
            //Loop to write random numbers to the file
            for(int k=0;k<current_size;++k)
                // Generate a random integer and write it to the file followed by a newline
                fprintf(file_ptr,"%d\n",rand());

            //Close the file
            fclose(file_ptr);

            printf("Generate file : %s\n", filename);      
        }
    }
    eTime = getCpuTime();
    printf("\nAll files have been generated successfully.\n");
    printf("Time Taken = %lf\n",eTime-sTime);
    return 0;
}