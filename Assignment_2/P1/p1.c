#include <stdio.h>
#include <string.h>
#include <mpi.h>
 
int main()
{
  MPI_Init(NULL, NULL);      
  int ID, num_proc;
  MPI_Comm_rank(MPI_COMM_WORLD, &ID);        
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);       
  printf("Process %d of %d : Hello World\n", ID, num_proc);
  MPI_Finalize();
  return 0;
}