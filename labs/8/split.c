#include <stdio.h>
#include "mpi.h"

int main(int argc,char **argv) {
  MPI_Init(NULL, NULL);

  MPI_Comm comm = MPI_COMM_WORLD;

  int rank;
  MPI_Comm_rank(comm, &rank);
  int size;
  MPI_Comm_size(comm, &size);
  
  int color = rank/4;

  MPI_Comm row_comm;
  MPI_Comm_split(MPI_COMM_WORLD, color, rank, &row_comm);
  
  int row_rank, row_size;
  MPI_Comm_rank(row_comm, &row_rank);
  MPI_Comm_size(row_comm, &row_size);
  
  printf("WORLD RANK/SIZE=%d/%d \t ROW RANK/SIZE=%d/%d \t color=%d\n",
	 rank, size, row_rank, row_size, color);
  
  MPI_Comm_free(&row_comm);
  MPI_Finalize();
  return 0;
}
