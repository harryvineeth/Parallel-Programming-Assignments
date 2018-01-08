#include "omp.h"
#include <stdio.h>

long double pi;
long double calculate(long double x)
{
	return (4.0/(1.0 + x * x));
}

int main()
{
	double start = omp_get_wtime();
	long long iterations = 100000;
	long double step = 1.0/(double)iterations;
	long long sum = 0;

	#pragma omp parallel
	{
		long double partial = 0;

		int id = omp_get_thread_num();
		int threads = omp_get_num_threads();

		for (int i = id ; i < iterations ; i += threads )
		{
			partial += calculate((i + 0.5) * step);
			
		}
		#pragma omp atomic
		sum = sum + partial;
	}	
	pi = sum * step;
	printf("PI Value = %Lf\n",pi);
	double end = omp_get_wtime();
	double time = end - start;
	printf("Time = %lf \n", time );
}
