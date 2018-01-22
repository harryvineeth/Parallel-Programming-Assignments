#include <stdio.h>
#include <mpi.h>

int main()
{
	MPI_Init(NULL, NULL);
	int ID, numproc;
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	MPI_Finalize();
	return 0;
}