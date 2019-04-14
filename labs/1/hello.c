#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
  int size, rank;
  char host[1024];
  int hostlen;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(host, &hostlen);

  printf("size=%d, rank=%d hostname=%s\n", size, rank, host);
  MPI_Finalize();
}
