#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
int n= argc<1 ? 20: atoi(argv[1]);
int rank, npes;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &npes);


int sum[n]; 
int message[n];
for (int i=0; i<n;++i){
	sum[i]=0;
	message[i]=rank;
}
MPI_Request request;

for(int j=0; j<npes; j++){
MPI_Isend(&message, n, MPI_INT, (rank==npes-1)? 0:rank+1,101,MPI_COMM_WORLD, &request);
for(int i=0; i<n ; ++i)
	sum[i]+=message[i];
MPI_Wait(&request,MPI_STATUS_IGNORE);
MPI_Recv(&message, n, MPI_INT, (rank==0)? npes-1:rank-1,101, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
printf("Process %d result is\n",rank);
for(int i=0;i<n;i++) printf("%d\n", sum[i]);
MPI_Finalize();
return 0;
}
