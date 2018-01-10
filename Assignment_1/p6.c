#include <stdio.h>
#include <omp.h>
#define ITERATIONS 100000

int main()
{
	int i;
	double start, end, time, step = 1.0 / ITERATIONS, sum = 0, PI;
	start = omp_get_wtime();
	#pragma omp parallel for reduction(+ : sum)
	for(i = 0; i < ITERATIONS; i++)
	{
		double x = (i + 0.5) * step;
		sum += 4 / (1 + x * x);
	}
	end = omp_get_wtime();
	PI = sum * step;
	time = end - start;
	printf("PI Value = %lf\n", PI);
	printf("Time = %lf\n", time );
	return 0;
}