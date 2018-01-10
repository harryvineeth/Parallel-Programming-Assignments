#include <stdio.h>
#include <omp.h>
#define N 1000

int a[N][N], b[N][N], ans[N][N];

void init_matrices()
{
	int j;
	#pragma omp parallel for
	for(j = 0; j < N * N; j++)
	{
		int x = j / N, y = j % N;
		a[x][y] = j;
		b[x][y] = 2 * j;
	}	
}

int dot_product(int x, int y)
{
	int sum = 0, k;
	for(k = 0; k < N; k++)
		sum = a[x][k] * b[k][y];
	return sum;
}

int main()
{
	int i, j, threads;
	double start, end, time, t1;	
	for(i = 1; i <= 16; i++)
	{
		omp_set_num_threads(i);
		init_matrices();
		start = omp_get_wtime();
		#pragma omp parallel
		{
			#pragma omp master
			threads = omp_get_num_threads();

			#pragma omp for
			for(j = 0; j < N * N; j++)
			{
				int x = j / N, y = j % N;
				ans[x][y] = dot_product(x, y);
			}
		}
		end = omp_get_wtime();
		time = end - start;
		if(threads == 1)
			t1 = time;
		printf("Speedup for %d threads = %lf\n", threads, t1 / time );
	}

	return 0;
}