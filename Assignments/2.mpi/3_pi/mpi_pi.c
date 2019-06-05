#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

double f(double x){
return 1/(1+x*x);
}


int main(int argc,char*argv[]){

long int n=100000000;
double h=1./n;
int rank;//store the MPI identifier of the process
int npes;//store the number of MPI processes
 
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&npes);

long int nloc=n/npes;
long int start=nloc*rank;
//int end=rank == (npes-1) ? start + n%npes + nloc: start+nloc;
int end=rank < (n%npes) ? start+nloc+1: start+nloc;
int reductor= npes-1;//the processor in which we reduce the final result
int printer=0;//the processor that will print the result

double start_time=MPI_Wtime();

double local_pi=0.0;
double global_pi=0.0;
for (long int i=start; i<=end-1;i++){
	double x_i=(i+0.5)*h;
	local_pi +=f(x_i);

};
local_pi=local_pi*4*h;

MPI_Reduce(&local_pi,&global_pi,1,MPI_DOUBLE,MPI_SUM,reductor,MPI_COMM_WORLD );

double duration= MPI_Wtime()-start_time;

if(rank==npes-1){
MPI_Send(&global_pi,1,MPI_DOUBLE,printer,101,MPI_COMM_WORLD);
}
if(rank==0){
MPI_Recv(&global_pi,1,MPI_DOUBLE,reductor,101,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("il valore di pi=%f calcolato in %f stampato dal processo %d\n ",global_pi,duration,printer);
}


MPI_Finalize();
 
return 0;
}
