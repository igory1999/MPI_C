#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main( int argc, char *argv[])
{
  char message[20];
  int myrank;
  MPI_Status status;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
  if (myrank == 0)
    {
      strcpy(message,"Hello");
      printf("Sent by rank %d: %s\n", myrank, message);
      MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    }
  else if (myrank == 1)
    {
      MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
      int count;
      MPI_Get_count(&status, MPI_CHAR, &count);
      printf("Received by rank %d: %s, count=%d\n", myrank, message, count);
    }
  MPI_Finalize();
  return 0;
}

