#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char **argv) {

  MPI_Init(NULL, NULL);

  MPI_Comm comm = MPI_COMM_WORLD;

  int rank;
  MPI_Comm_rank(comm, &rank);
  int size;
  MPI_Comm_size(comm, &size);

  if (size<2) {
    printf("This program needs at least 2 processes\n");
    return -1;
  }

  int new_rank,new_size;
  MPI_Comm sharedcomm;

  MPI_Info info;
  MPI_Comm_split_type(MPI_COMM_WORLD,MPI_COMM_TYPE_SHARED,rank,info,&sharedcomm);
  MPI_Comm_size(sharedcomm,&new_size);
  MPI_Comm_rank(sharedcomm,&new_rank);


  char procname[1024];
  int namlen;
  MPI_Get_processor_name(procname,&namlen);
  printf("local rank = %d, local size = %d, global rank = %d, global size = %d, %s\n",
	 new_rank, new_size, rank, size, procname);
  
  MPI_Finalize();
  return 0;
}

