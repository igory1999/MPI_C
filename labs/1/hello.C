#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
  int size, rank;
  char host[1024];
  int hostlen;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(host, &hostlen);

  cout << "size=" << size << ", rank=" << rank << ", host=" << host << endl;

  MPI_Finalize();

}
