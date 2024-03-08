#include <iostream>
#include <omp.h>     // OpenMP library for parallel programming


using namespace std;

#define Size 10000   // Size of the array to be sorted

void SelectionSort_ParallelVersion(int arr[], int size) {
#pragma omp parallel for 
    // Parallel loop for iterating through the array elements
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;   // Index of the minimum element
        int minValue = arr[i];  // Value of the minimum element

        // Find the minimum element in the unsorted part of the array
#pragma omp parallel for reduction(min:minValue) shared(arr)
        // Parallel loop for finding the minimum element
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < minValue) {  // If current element is smaller than minimum value
                minIndex = j;   // Update the index of minimum element
                minValue = arr[j];  // Update the value of minimum element
            }
        }

        // Swap the minimum element with the first element of the unsorted part
        if (minIndex != i) {
#pragma omp critical
            swap(arr[i], arr[minIndex]);  // Swap operation
        }
    }
}

int main() {

    // Initialize an array of size ARRAY_SIZE
    int MY_ARRAY[Size];

    // Fill the array with random numbers
    for (int i = 0; i < Size; ++i) {
        MY_ARRAY[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    cout << "Array before sorting: ";
    for (int i = 0; i < 50; ++i) {
        cout << MY_ARRAY[i] << " ";  // Output array before sorting
    }

    // Sort the array using parallel selection sort
    SelectionSort_ParallelVersion(MY_ARRAY, Size);

    cout << "\nArray after sorting: ";
    for (int i = 0; i < 50; ++i) {
        cout << MY_ARRAY[i] << " ";  // Output array after sorting
    }

    return 0;
}
