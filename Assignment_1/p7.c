#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MOD 2147483647
#define ADDEND 12345
#define MULTIPLIER 1103515245
#define ITERATIONS 10000000

long long rand_last = 0, LEAP_MULTIPLIER, LEAP_ADDEND;
#pragma omp threadprivate(rand_last)

long long modexp(long long base, long long exp)
{
	long long ans = 1;
	while(exp)
	{
		if(exp % 2)
			ans = (ans * base) % MOD;
		base = (base * base) % MOD;
		exp = exp >> 1; 
	}
	return ans;
}

double get_rand()
{
	long long rand_next = ((rand_last * LEAP_MULTIPLIER) % MOD + LEAP_ADDEND) % MOD;
	rand_last = rand_next;
	return (double)rand_next / MOD;
}

int inside_circle(double x, double y)
{
	return ((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5) < 0.25) ? 1 : 0;
}

int main()
{
	int inside_circle_points = 0, threads, i; 
	long long *threads_seeds;
	double start, end, time, PI;
	start = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		{
			threads = omp_get_num_threads();
			threads_seeds = (long long*) malloc(sizeof(long long) * threads);
			threads_seeds[0] = MOD / MULTIPLIER;
			for(i = 1; i < threads; i++)
				threads_seeds[i] = ((MULTIPLIER * threads_seeds[i - 1]) % MOD + ADDEND) % MOD;
			LEAP_MULTIPLIER = modexp(MULTIPLIER, threads);
			LEAP_ADDEND = (ADDEND * ((LEAP_MULTIPLIER - 1 + MOD) % MOD * modexp(MULTIPLIER - 1, MOD - 2)) % MOD) % MOD;
		}
		int ID = omp_get_thread_num();
		rand_last = threads_seeds[ID];

		#pragma omp for reduction(+ : inside_circle_points)
		for(i = 0; i < ITERATIONS; i++)
		{
			double x = get_rand(), y = get_rand();
			if(inside_circle(x, y))
				inside_circle_points++;
		}
 	}
	end = omp_get_wtime();
	PI = 4 * (double)inside_circle_points / ITERATIONS;
	end = omp_get_wtime();
	time = end - start;
	printf("PI Value = %lf\n", PI);
	printf("Time = %lf\n", time );
	return 0;
}