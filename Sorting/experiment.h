#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "intSort.h"   
#include "miscfn.h"    
#include "cpuTimer.h"  

#define FILES_PER_SIZE 30

// List of sizes
int sizes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 32, 64, 125, 250, 500, 1000, 2000, 4000, 8000, 16000, 30000, 50000, 100000, 250000};
int countIndex = sizeof(sizes) / sizeof(sizes[0]);

// // Structure to hold single-run results
// typedef struct {
//     double cpu_time;
//     long long swaps;
//     long long comparisons;
// } run_result_t;

// Public functions
void ensure_data_files_exist(void); // create files if missing
void run_experiment_all_algos(void); // main driver: runs all sorting algos
void run_experiment_for_algo(const char* algo_name,
                            long long (*sort_func)(int[], int, long long*));
void write_csv_for_algo(const char* algo_name, const int sizes[], int num_sizes,
                        double avg_time[], double sd_time[],
                        double avg_swaps[], double sd_swaps[],
                        double avg_comps[], double sd_comps[]);
void fit_quadratic_and_write(const char* algo_name, const int sizes[], int num_sizes,
                             const double y[]); // fit y vs size

#endif // EXPERIMENT_H_
