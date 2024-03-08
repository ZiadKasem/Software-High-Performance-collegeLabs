#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

#define N 100 //fixed size of the array
#define MOD 20 // Mod to limite the maximum value

int main()
{
    int arr[N]; // decleration of the array
    

    // Fill the array with random numbers
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % MOD;
    }
    // tid is variable to store thread id
    // nthread determines the number of threads will be created
    int tid, nthreads = 4; 
#pragma omp parallel private(tid) num_threads(nthreads)
    {
     
        tid = omp_get_thread_num();// Get the thread ID of each thread

        for (int i = tid * (N / nthreads); i < (tid + 1) * (N / nthreads); i++) {
            // Check if the current element in the array is equal to 15
            if (arr[i] == 15) {
                // print the tid if element found equals 15
                cout << "tid is " << tid << ", index is " << i<<endl;
            }
        }


    }

    return 0;
}