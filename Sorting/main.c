#include<stdio.h>
#include "cpuTimer.h"
#include "intSort.h"
#include "miscfn.h"

#define FILES_PER_SIZE 30

void main()
{
    int sizes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 30000, 50000, 100000, 250000};
    int countIndex = sizeof(sizes) / sizeof(sizes[0]);

    char* sorts[6] = {"Bubble", "Insert","Quick","Heap","Select","Shell"};
    printf("Choose Sorting Algorithm:\n");
    for(int i=0;i<6;++i)
        printf("%d. %sSort\n",i+1,sorts[i]);
    printf("Enter choice (1-6): ");
    int choice;
    scanf("%d",&choice);
    if(choice<1 || choice>6){
        printf("Invalid choice. Exiting.\n");
        return;
    }

    

    for (int i=0;i<countIndex;++i)
    {
        double cpuTimes[FILES_PER_SIZE];
        long long comparisonsArr[FILES_PER_SIZE];
        long long swapsArr[FILES_PER_SIZE];
        int current_size = sizes[i];
        char foldername[50];
        sprintf(foldername, "SIZE_%07d", current_size);
        char filename[150];
        FILE *file_ptr;
        for(int j=1;j<=FILES_PER_SIZE;++j){
            sprintf(filename, "%s/RANDOM_%07d_%02d.dat", foldername, current_size, j);
            file_ptr = fopen(filename,"r");
            if(file_ptr == NULL){
                fprintf(stderr,"Error: Could not open file %s for reading.""Skipping.\n",filename);
                continue; //Skip to the next file
            } 
            int *arr = (int *)malloc(sizeof(int) * current_size);
            for(int k=0;k<current_size;++k)
                fscanf(file_ptr,"%d",&arr[k]);
            fclose(file_ptr);

            long long swaps=0, comparisons=0;
            double sTime = 0, eTime = sTime; // Initialize times
            switch (choice) {
                case 1:
                    sTime = getCpuTime();
                    comparisons = bubbleSort(arr,  current_size , &swaps); // Call bubbleSort
                    eTime = getCpuTime();
                    break;
                case 2:
                    sTime = getCpuTime();
                    comparisons = insertSort(arr,  current_size , &swaps); // Call insertSort
                    eTime = getCpuTime();
                    break;
                case 3:
                    sTime = getCpuTime();
                    comparisons = quickSort(arr,  current_size , &swaps); // Call quickSort
                    eTime = getCpuTime();
                    break;
                case 4:
                    sTime = getCpuTime();
                    comparisons = heapSort(arr,  current_size , &swaps); // Call heapSort
                    eTime = getCpuTime();
                    break;
                case 5:
                    sTime = getCpuTime();
                    comparisons = selectSort(arr,  current_size , &swaps); // Call selectSort
                    eTime = getCpuTime();
                    break;
                case 6:
                    sTime = getCpuTime();
                    comparisons = shellSort(arr,  current_size , &swaps); // Call shellSort
                    eTime = getCpuTime();
                    break;
                default:
                    printf("Invalid choice. Exiting.\n");
                    free(arr);
                    return;
            }
            double cpu_time = eTime - sTime;
            cpuTimes[j-1] = cpu_time;
            comparisonsArr[j-1] = comparisons;
            swapsArr[j-1] = swaps;
            char sorted_filename[150];
            sprintf(sorted_filename, "%s/SORTED_%s_%07d_%02d.dat", foldername,sorts[choice-1], current_size, j);
            FILE *sorted_file = fopen(sorted_filename, "w");
            if (sorted_file == NULL) {
                fprintf(stderr, "Error: Could not open file %s for writing.\n", sorted_filename);
                continue;
            }
            for (int k = 0; k < current_size; ++k) {
                fprintf(sorted_file, "%d\n", arr[k]);
            }
            fclose(sorted_file); 

                                   
            free(arr);
        }


        char analysis_filename[150];
        sprintf(analysis_filename, "ANALYSIS_%s.csv", sorts[choice-1]);

        int is_new_file = 0;
        FILE *check_file = fopen(analysis_filename, "r");
        if (check_file == NULL) {
        is_new_file = 1;  // File doesn't exist
        }
        fclose(check_file);

        FILE *analysis_file = fopen(analysis_filename, "a");
        if (analysis_file == NULL) {
            printf("Error: Could not open file %s for appending.\n", analysis_filename);
            continue;
        }
        if (is_new_file) {
            fprintf(analysis_file, "SizeOfArray,AvgTime,SDtime,AvgComparisons,AvgSwaps,SDcomparisions,SDswaps\n");
            printf("SizeOfArray,AvgTime,SDtime,AvgComparisons,AvgSwaps,SDcomparisions,SDswaps\n");
        }
        double avgCpuTime = calcAvg(cpuTimes,FILES_PER_SIZE);
        double sdCpuTime = calcSD(cpuTimes,FILES_PER_SIZE,avgCpuTime);
        double avgComps = calcAvgLL(comparisonsArr,FILES_PER_SIZE);
        double sdComps = calcSDLL(comparisonsArr,FILES_PER_SIZE,avgComps);
        double avgSwaps = calcAvgLL(swapsArr,FILES_PER_SIZE);
        double sdSwaps = calcSDLL(swapsArr,FILES_PER_SIZE,avgSwaps);
        fprintf(analysis_file, "%d,%g,%g,%g,%g,%g,%g\n", current_size, avgCpuTime,sdCpuTime,avgComps,avgSwaps,sdComps,sdSwaps);
        fclose(analysis_file);
        
        // printf("%-11d,%-7g,%-6g,%-13g,%-8g,%-14g,%-7g\n", 
            // current_size, avgCpuTime, sdCpuTime, avgComps, avgSwaps, sdComps, sdSwaps);
        printf("%d,%g,%g,%g,%g,%g,%g\n", current_size, avgCpuTime,sdCpuTime,avgComps,avgSwaps,sdComps,sdSwaps);
    }
    
}