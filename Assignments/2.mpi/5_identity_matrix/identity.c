#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


//function to print the matrix
void print_matrix(int *mat,int n_loc,int n,FILE *outfile){
for (int i=0;i<n_loc;i++){
	for(int j=0;j<n;j++){
		fprintf(outfile,"%d ", mat[i*n+j]);
		}
	fprintf(outfile,"\n");
	}
}

//function to swap pointers
void swap(int**p1,int**p2){
int *tmp=*p1;
*p1=*p2;
*p2=tmp;
}


int main(int argc, char* argv[]){
size_t n=argc<1? 30:atoi(argv[1]);
int rank=0;
int npes=1;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &npes);
MPI_Request request;


double start=MPI_Wtime();
int rest=n%npes;
int n_loc=rank < rest ? n/npes+1: n/npes;


int *mat=(int*)malloc(n_loc*n*sizeof(int));

for (int i=0;i<n_loc;i++){
	int i_global= i+(rank*n_loc)+ ((rank < rest) ? 0 : rest);
	for(int j=0;j<n;j++){
		if(i_global==j) mat[i*n+j]=1;
		else mat[i*n+j]=0;
	}
}

if(!rank){
	FILE *output_file=(n<=10)?stdout: fopen("identity_matrix.txt","w");
	int *recv_buf=(int*)malloc(n_loc*n*sizeof(int));
	for(int count=1;count<npes;count++){
		MPI_Irecv(recv_buf,n*n_loc,MPI_INT,count,101,MPI_COMM_WORLD,&request);
		if(count>rest && rest > 0 ) print_matrix(mat,n_loc-1,n,output_file);
		else print_matrix(mat, n_loc,n, output_file);
		MPI_Wait(&request, MPI_STATUS_IGNORE);
		swap(&recv_buf,&mat);
	}
	if(rest >0) print_matrix(mat,n_loc-1,n,output_file);
	else print_matrix(mat,n_loc,n,output_file);
	free(recv_buf);
	fclose(output_file);
}

else MPI_Send(mat,n_loc*n,MPI_INT,0,101,MPI_COMM_WORLD);

free(mat);

//to measure the computation time
double duration=MPI_Wtime()-start;
if(!rank) printf("time required %f\n",duration);

MPI_Finalize();

return 0;

}
