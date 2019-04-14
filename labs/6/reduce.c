#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

int main(int argc,char **argv) {

  MPI_Init(NULL, NULL);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  srand(rank + time(NULL));
  float myrandom = (float) rand()/(float)RAND_MAX, result;
  int target_proc = size - 1;

  printf("rank = %d myrandom = %f\n", rank, myrandom);

  
  MPI_Reduce(&myrandom,&result,1,MPI_FLOAT,MPI_SUM,
             target_proc,MPI_COMM_WORLD);
  if (rank == target_proc)
    printf("Result %6.3f compared to size/2=%5.2f\n",
           result,size/2.);

  MPI_Finalize();
  return 0;
}
