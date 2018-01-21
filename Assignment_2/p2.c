#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void init_vectors(double **X, double **Y)
{
	*X = (double*)malloc(sizeof(double)*(1 << 16));
	*Y = (double*)malloc(sizeof(double)*(1 << 16));
	int i;
	for(i = 0; i < 1 << 16; i++)
	{
		(*X)[i] = i;
		(*Y)[i] = 2 * i;
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
	double *X, *Y, *sub_X, *sub_Y, start, end;
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	if(ID == 0)
	{
		init_vectors(&X, &Y);
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
		printf("Time taken by %d processes : %lf seconds\n", num_proc, end - start);
	}
	MPI_Finalize();
	return 0;
}