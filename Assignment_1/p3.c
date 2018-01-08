#include <omp.h>
#include <stdio.h>
int main()
{
	int X[1 << 16];
	int Y[1 << 16];
	float a = 0.7;
	int i, j, thread;	
	double start, end, t1;
	for( int i = 0; i < 1 << 16; i++ )
	{
		X[i] = i;
		Y[i] = 2 * i;
	}

	for( i = 1 ; i <= 8 ; i++ )
	{
		omp_set_num_threads(i);	
		start = omp_get_wtime();
		#pragma omp parallel
		{
			#pragma omp master
			threads = omp_get_num_threads();
			
			#pragma omp for
			for( j = 0 ; j < (1 << 16) ; j++)
				X[j] = a * X[j] + Y[j];
			
		}
		end = omp_get_wtime();
		double time = end - start;
		if(thread == 1)
			t1 = time;
		printf("Time used for thread %d = %lf \nSpeedup for %d threads = %lf\n\n", threads, time, threads, t1 / time );
	}
	return 0;
}
