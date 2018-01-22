#include <stdio.h>
#include <mpi.h>


int main()
{
	int rank, i;
	MPI_Status status;
	struct 
	{
		int I;
		float F;
		double D[4];
	} data;

	int blocklengths[3] = {1, 1, 4};
	MPI_Datatype types[3] = {MPI_INT, MPI_FLOAT, MPI_DOUBLE};
	MPI_Aint displacements[3];
	MPI_Datatype restype;
	MPI_Aint intex,floatex;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Type_extent(MPI_INT,&intex);
	MPI_Type_extent(MPI_FLOAT,&floatex);
	displacements[0] = (MPI_Aint) 0; 
	displacements[1] = intex;
	displacements[2] = intex + floatex;
	MPI_Type_struct(3,blocklengths,displacements,types,&restype);
	MPI_Type_commit(&restype);

	if (rank == 3)
	{
		data.I = 6; 
		data.F = 3.14; 
		for(i = 0; i < 4; ++i) 
			data.D[i] = (double) i+1;

		MPI_Send(&data,1,restype,1,52,MPI_COMM_WORLD);
	} 
	else if(rank == 1) 
	{
		MPI_Recv(&data,1,restype,3,52,MPI_COMM_WORLD,&status);
		printf("Structure recieved by :%d \nData transferred is\n %d\n %f\n %lf %lf %lf %lf\n",rank,data.I,data.F,data.D[0],data.D[1],data.D[2],data.D[3]);
	}
	
	MPI_Finalize();
	return 0;
}