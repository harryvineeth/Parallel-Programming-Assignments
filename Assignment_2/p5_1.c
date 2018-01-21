#include <stdio.h>
#include <mpi.h>

int main()
{
	MPI_Init(NULL, NULL);
	int ID, num_proc, my_val = 1, recv_val;
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);
	MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	while(num_proc > 1 && ID < num_proc)
	{
		if(num_proc % 2 == 1 && ID == num_proc - 1)
			MPI_Send(&my_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		else if(ID >= num_proc / 2)
			MPI_Send(&my_val, 1, MPI_INT, ID - num_proc / 2, 0, MPI_COMM_WORLD);
		else 
		{
			MPI_Recv(&recv_val, 1, MPI_INT, ID + num_proc / 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			my_val += recv_val;
			if(num_proc % 2 == 1 && ID == 0)
			{
				MPI_Recv(&recv_val, 1, MPI_INT, num_proc - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				my_val += recv_val;
			}
		}
		num_proc = num_proc >> 1;
	}
	if(ID == 0)
		printf("Final Value : %d\n", my_val);
	MPI_Finalize();
	return 0;
}