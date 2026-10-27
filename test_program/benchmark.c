#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define SIZE 400

int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];

int main() {
    struct timespec start_real, end_real;
    struct rusage usage;
    
    // 初始化矩陣
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }

    printf("Starting CPU-bound matrix multiplication...\n");
    
    // 記錄現實開始時間
    clock_gettime(CLOCK_MONOTONIC, &start_real);

    // 矩陣乘法 (CPU 密集運算)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // 記錄現實結束時間
    clock_gettime(CLOCK_MONOTONIC, &end_real);
    
    // 取得 CPU 使用時間數據
    getrusage(RUSAGE_SELF, &usage);

    // 計算時間
    double real_time = (end_real.tv_sec - start_real.tv_sec) + 
                       (end_real.tv_nsec - start_real.tv_nsec) / 1000000000.0;
                       
    double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0;
    double sys_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0;
    double cpu_time = user_time + sys_time;
    
    // 計算 CPU Utilization
    double cpu_utilization = (cpu_time / real_time) * 100.0;

    printf("Execution Time (Real Time): %f seconds\n", real_time);
    printf("CPU Time (User + Sys): %f seconds\n", cpu_time);
    printf("CPU Utilization: %.2f %%\n", cpu_utilization);
    
    double operations = (double)SIZE * SIZE * SIZE;
    double throughput = (operations / real_time) / 1000000.0;
    printf("Throughput: %f MOPs\n", throughput);

    return 0;
}
