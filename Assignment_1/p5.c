#include <omp.h>
#include <stdio.h>
#define ITERATIONS 100000

int main()
{
	double start, end, time, step = 1.0 / ITERATIONS, PI;
	start = omp_get_wtime();
	#pragma omp parallel
	{
		double sum = 0;
		int i, ID = omp_get_thread_num(), threads = omp_get_num_threads();
		for (i = ID; i < ITERATIONS; i += threads)
		{
			double x = (i + 0.5) * step;
			sum += 4 / (1 + x * x);
		}
		#pragma omp atomic
		PI = PI + sum;
	}	
	end = omp_get_wtime();
	PI = PI * step;
	time = end - start;
	printf("PI Value = %lf\n", PI);
	printf("Time = %lf\n", time );
	return 0;
}
