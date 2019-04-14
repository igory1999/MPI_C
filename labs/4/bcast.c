#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc,char **argv) {
  int input_argument, procno;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &procno);
  
  if (procno==0) {
    if ( argc==1 || ( argc>1 && !strcmp(argv[1],"-h") ) ) {
      printf("\nUsage: bcast [0-9]+\n");
      MPI_Abort(MPI_COMM_WORLD,1);
    }
    input_argument = atoi(argv[1]);
  }
  MPI_Bcast(&input_argument,1,MPI_INT,0,MPI_COMM_WORLD);
  printf("Processor %d gets %d\n",procno,input_argument);

  MPI_Finalize();
  return 0;
}
