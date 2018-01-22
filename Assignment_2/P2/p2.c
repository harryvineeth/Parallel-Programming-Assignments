#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void init_vectors(double X[], double Y[])
{
	int i;
	for(i = 0; i < 1 << 16; i++)
	{
		X[i] = i;
		Y[i] = 2 * i;
	}	
}

void compute_DAXPY(double X[], double Y[], int n)
{
	int i;
	double a = 3.0;
	for(i = 0; i < n; i++)
		X[i] = a * X[i] + Y[i];
}

int main()
{	
	MPI_Init(NULL, NULL);
	int ID, num_proc, size_per_process;
	double *X, *Y, *sub_X, *sub_Y, start, end, time, t1;
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	if(ID == 0)
	{
		// Serial section
		X = (double*) malloc(sizeof(double) * (1 << 16));
		Y = (double*) malloc(sizeof(double) * (1 << 16));
		init_vectors(X, Y);
		start = MPI_Wtime();
		compute_DAXPY(X, Y, 1 << 16);
		end = MPI_Wtime();
		t1 = end - start;
		// Parallel section
		init_vectors(X, Y);
		start = MPI_Wtime();
	}
	size_per_process = (1 << 16) / num_proc;
	sub_X = (double*)malloc(sizeof(double) * size_per_process);
	sub_Y = (double*)malloc(sizeof(double) * size_per_process);
	MPI_Scatter(X, size_per_process, MPI_DOUBLE, sub_X, size_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(Y, size_per_process, MPI_DOUBLE, sub_Y, size_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	compute_DAXPY(sub_X, sub_Y, size_per_process);
	MPI_Gather(sub_X, size_per_process, MPI_DOUBLE, X, size_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if(ID == 0)
	{
		end = MPI_Wtime();
		time = end - start;
		printf("Time taken by %d processes : %lf seconds\n", num_proc, time);
		printf("Speedup for %d processes : %lf\n", num_proc, time / t1);
		free(X); free(Y);
	}
	MPI_Finalize();
	return 0;
}