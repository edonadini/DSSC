#include <stdio.h>
#include<stdlib.h>

#define nths 1024
#define n 8192

_global_ void mat_transp(double* m_in, double *m_out){
j=blockIdx.x;
i=threadIdx.x;
while(i<n){
m_out(i*n+j)=m_in(j*n+i);
i+=blockDim.x;}
}

_global_ void mat_fast_transp(){

}

int main(&argc, &argv[]){

double *mat_in_h, *mat_out_h, *mat_in_d, *mat_out_d;
int size=n*n*sizeof(double);
int nblock=(n*n)/nths;

mat_in_h=(double*)malloc(size);
mat_out_h=(double*)malloc(size);

cudaMalloc(&mat_in_d,size);
cudaMalloc(&mat_out_d,size);

//inizialize the matrix
for(int i=0;i<(n*n);i++) mat_in_h[i]=(double) i;

//move data from CPU to GPU
cudaMemcpy( mat_in_d, mat_in_h, size, cudaMemcpyHostToDevice);

//run a kernel
mat_transp<<<nblock,nths>>>( mat_in_d, mat_out_d);
cudaMemcpy( mat_out_h, mat_out_d, size, cudaMemcpyDeviceToDevice);

free(mat_in_h);
free(mat_out_h);
cudaFree(mat_in_d);
cudaFree(mat_out_h);
return 0;
}
