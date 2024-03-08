#include<stdio.h>
#include <omp.h>
#include<windows.h>
#include<Math.h>
int main()
{
	int nPoints = 10000000;// Total number of random points to generate
	int tid, nthreads = 8;// Variables for thread ID and number of threads
	double nInside = 0;// Counter for points inside the circle
	double rand_x, rand_y;// Variables to store random coordinates
#pragma omp parallel private(tid,rand_x,rand_y) reduction(+:nInside) num_threads(nthreads)
	{
		tid = omp_get_thread_num();
		// Determine the range of points for this thread
		int start = tid*(nPoints/nthreads) ;
		int end = (tid+1) * (nPoints / nthreads);
		
		// for loop to Generate random points and check if they are inside the circle
		for (int i = start; i < end; i++) {
			rand_x = (double)(rand() % 100) / 100.0;
			rand_y = (double)(rand() % 100) / 100.0;
			/*
			* check if the point inside the circle or not
			* if inside, increment the Inside variable
			*/
			if (sqrt(rand_x * rand_x + rand_y * rand_y) <= 1.0) {
				nInside++;
			}
		}
	}
	// print PI value which equals (#points inside circle / total #points) * 4
	printf("Estimated value of Pi: %f\n", (4.0 * nInside) / nPoints);
}