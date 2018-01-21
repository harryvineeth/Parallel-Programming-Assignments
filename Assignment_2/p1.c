#include <stdio.h>
#include <string.h>
#include <mpi.h>
 
int main()
{
  MPI_Init(NULL, NULL);      
  int ID, num_proc;
  MPI_Comm_rank(MPI_COMM_WORLD, &ID);        
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);       
  if(ID != 0)
  {
  	char* message;
  	sprintf(message, "Message from process %d to process 0", ID);
  	MPI_Send(message, strlen(message), MPI_CHAR, 0, 0, MPI_COMM_WORLD)
  }
  else
  {
  	MPI_Status = status;
  	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
  		
  }
  printf("Process %d of %d : Hello World\n", ID, num_proc);
  MPI_Finalize();
  return 0;
}