#include <omp.h>
#include <stdio.h>

int X[1 << 16], Y[1 << 16];

void init_vectors()
{
	int j;
	#pragma omp parallel for
	for(j = 0; j < 1 << 16; j++)
	{
		X[j] = j;
		Y[j] = 2 * j;
	}	
}

int main()
{
	int i, j, threads, a = 3;	
	double start, end, time, t1;
	for(i = 1 ; i <= 16 ; i++)
	{
		omp_set_num_threads(i);		
		init_vectors();	
		start = omp_get_wtime();
		#pragma omp parallel
		{
			#pragma omp master
			threads = omp_get_num_threads();
			
			#pragma omp for
			for(j = 0; j < 1 << 16; j++)
				X[j] = a * X[j] + Y[j];
			
		}
		end = omp_get_wtime();
		time = end - start;
		if(threads == 1)
			t1 = time;
		printf("Speedup for %d threads = %lf\n", threads, t1 / time );
	}
	return 0;
}