#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main ()
{
	MPI_Init(NULL, NULL);
	int ID, num_proc, num_steps, i;
	double final_PI, partial_PI = 0, sum = 0, start, end;
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	if(ID == 0)
	{
		num_steps = 100000;
		start = MPI_Wtime();
	}	
	MPI_Bcast(&num_steps, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = ID; i < num_steps; i += num_proc)
	{
		double x = (i + 0.5) / num_steps;
		sum = sum + 4 / (1 + x * x);
	}
	partial_PI = sum / num_steps;
	MPI_Reduce(&partial_PI, &final_PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(ID == 0)
	{	
		end = MPI_Wtime();
		printf("Process 0 : PI value = %lf\n", final_PI);
		printf("Time taken by %d processes : %lf seconds\n", num_proc, end - start);
	}
	MPI_Finalize();
	return 0;
}