#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>

///////library for execution time
#include <chrono>
using namespace std::chrono;
using namespace std;
#define N 10000
int main() {

	/*Start time*/
	auto start = high_resolution_clock::now();

	int nthreads = 4;
	int a[N];
	int count = 0;

	for (int i = 0; i < N; i++)
		a[i] = rand() % 50;

	// parallel processing block static schedule with chunk 5
#pragma omp parallel for schedule(guided,5) reduction(+:count) num_threads(nthreads)

	for (int i =0; i < N; i++) {
		/*Search in array and count how many numbers are less than or equal 25*/
		if (a[i] <= 25) {
			count++;
		}
	}
	/*Stop time and calculate duration*/
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	
	/*Print duration and answer*/
	cout <<"Time "<< duration.count() << endl;
	cout << count << endl;
}