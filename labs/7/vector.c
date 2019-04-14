#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mpi.h"


void print_array(double *a, int len, char *message, int rank)
{
  printf("%s:\trank=%d\n", message, rank);
  for(int i = 0; i < len; i++)
    {
      printf("%f ", a[i]);
    }
  printf("\n");
}


int main(int argc,char **argv) {
  MPI_Init(NULL, NULL);

  MPI_Comm comm = MPI_COMM_WORLD;
  
  int procno;
  MPI_Comm_rank(comm, &procno);
  int nprocs;
  MPI_Comm_size(comm, &nprocs);

  if (nprocs<2) {
    printf("This program needs at least two processes\n");
    return -1;
  }
  int sender = 0, receiver = 1, the_other = 1-procno,
    count = 5, stride=2, blocklen=1;
  double *source,*target;
  source = (double*) malloc(stride*count*sizeof(double));
  target = (double*) malloc(count*blocklen*sizeof(double));

  for(int i = 0; i<stride*count; i++)
    source[i] = i+.5;

  MPI_Datatype newvectortype;
  if (procno==sender) {
    MPI_Type_vector(count,blocklen,stride,MPI_DOUBLE,&newvectortype);
    MPI_Type_commit(&newvectortype);
    MPI_Send(source, 1, newvectortype, receiver, 0, comm);
    MPI_Type_free(&newvectortype);
    print_array(source, stride*count, "In send", procno);
  } else if (procno==receiver) {
    MPI_Status recv_status;
    int recv_count;
    MPI_Recv(target, count, MPI_DOUBLE, sender, 0, comm,
             &recv_status);
    MPI_Get_count(&recv_status, MPI_DOUBLE, &recv_count);
    assert(recv_count==count);
    print_array(target, count*blocklen, "In recieve", procno);    
  }
  
  if (procno==receiver) {
    for(int i=0; i<count; i++)
      if (target[i]!=source[stride*i])
	printf("location %d %e s/b %e\n",i,target[i],source[stride*i]);
  }

  if (procno==0)
    printf("Finished\n");

  MPI_Finalize();
  return 0;
}
