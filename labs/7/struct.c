#include <stdio.h>
#include "mpi.h"

struct object
{
  char c;
  double x[2];
  int i;
};

void print_struct(struct object *o, char *message)
{
  printf("%s c = %c, x = [%f, %f], i = %d\n",
	 message, o->c, o->x[0], o->x[1], o->i);
}

int main(int argc, char **argv)
{

  MPI_Init(NULL, NULL);
  MPI_Comm comm = MPI_COMM_WORLD;
  
  int procno;
  MPI_Comm_rank(comm, &procno);
  int nprocs;
  MPI_Comm_size(comm, &nprocs);

  if (nprocs<2)
    {
      printf("This program needs at least two processes\n");
      return -1;
    }
  
  int sender = 0, receiver = 1, the_other = 1-procno;

  MPI_Datatype newstructuretype;
  int structlen = 3;
  int blocklengths[structlen]; 
  MPI_Datatype types[structlen];
  MPI_Aint displacements[structlen];

  struct object myobject;
  
  blocklengths[0] = 1;
  types[0] = MPI_CHAR;
  displacements[0] = (size_t)&(myobject.c) - (size_t)&myobject;
  
  blocklengths[1] = 2;
  types[1] = MPI_DOUBLE;
  displacements[1] = (size_t)&(myobject.x[0]) - (size_t)&myobject;
  
  blocklengths[2] = 1;
  types[2] = MPI_INT;
  displacements[2] = (size_t)&(myobject.i) - (size_t)&myobject;

  MPI_Datatype newstructure;
  
  MPI_Type_create_struct(structlen, blocklengths, 
			 displacements, types, &newstructure);
  MPI_Type_commit(&newstructure);

  {
    MPI_Aint typesize;
    MPI_Type_extent(newstructure,&typesize);
    if(procno==0) 
      printf("Type extent: %ld bytes\n",typesize);
  }
  
  if (procno==sender)
    {
      myobject.c = 'a';
      myobject.x[0] = 1.3;
      myobject.x[1] = 2.7;
      myobject.i = 9;
      print_struct(&myobject, "Sending:\t");
      MPI_Send(&myobject,1,newstructure,the_other,0,comm);
    } else if (procno==receiver)
    {
      MPI_Recv(&myobject,1,newstructure,the_other,0,comm,
	       MPI_STATUS_IGNORE);
      print_struct(&myobject, "Recieving:\t");      
    }
  MPI_Type_free(&newstructure);
  MPI_Finalize();
  return 0;

}
