#include <stdio.h>
#include<stdlib.h>

#define nths 1024
#define n 8192 //size of the matrix
#define dim 32

typedef void(*kernelFunc)(double*,double*,int);

__global__ void mat_transp(double* m_in, double *m_out, int siz){
int row=blockIdx.x*blockDim.x+threadIdx.x;
int col=blockIdx.y*blockDim.y+threadIdx.y;
m_out[col*siz+row]=m_in[row*siz+col];
}

__global__ void mat_fast_transp(double *m_in, double *m_out, int siz){
__shared__ double tile[dim][dim];
int col=blockIdx.x*blockDim.x +threadIdx.x;
int row=blockIdx.y*blockDim.y +threadIdx.y;
tile[threadIdx.x][threadIdx.y]=m_in[row*siz+col];
__syncthreads();
m_out[col*siz+row]=tile[threadIdx.x][threadIdx.y];
}

int correctness(double *m_in,double *m_out, int siz){
for (int i=0;i<siz; ++i)
	for(int j=0;j<siz; ++j)
		if(m_out[i*siz+j]!=m_in[j*siz+i])
			return 0;
return 1;
}

int TestCuda(kernelFunc kernel,const char *kernelName, int block_x, int block_y){
int size= n*n*sizeof(double);
double *mat_in_h, *mat_out_h, *mat_in_d, *mat_out_d;

dim3 block(block_x, block_y);
dim3 grid(n/block.x, n/block.y);

mat_in_h=(double*)malloc(size);
mat_out_h=(double*)malloc(size);

cudaMalloc((void **)&mat_in_d,size);
cudaMalloc((void **)&mat_out_d,size);

//inizialize the matrix
for(int i=0;i<(n*n);i++) mat_in_h[i]= i;

//move data from CPU to GPU
cudaMemcpy( mat_in_d, mat_in_h, size, cudaMemcpyHostToDevice);

//timing
cudaEvent_t start, stop;
cudaEventCreate(&start);
cudaEventCreate(&stop);

cudaEventRecord(start);
//run a kernel
kernel<<<grid,block>>>( mat_in_d, mat_out_d, dim);
cudaEventRecord(stop);
cudaEventSynchronize(stop);
//move data from GPU to CPU
cudaMemcpy( mat_out_h, mat_out_d, size, cudaMemcpyDeviceToHost);

//verify the correctness
printf("%s: %s\n",kernelName,correctness(mat_in_h,mat_out_h,size)? "Correct":"Fail");

float milliseconds=0;
cudaEventElapsedTime(&milliseconds, start, stop);
printf("Time in milliseconds: %f\n", milliseconds);
printf("Bandwidth: %f GB/s\n", 2*size/milliseconds/1e6);
printf("-------------------\n");

//Cleanup
free(mat_in_h);
free(mat_out_h);
cudaFree(mat_in_d);
cudaFree(mat_out_h);
cudaEventDestroy(start);
cudaEventDestroy(stop);
return 0;
}

int main(int argc, char*argv[]){
TestCuda(&mat_transp,"Naive Transpose threads per block 64", 8,8);
TestCuda(&mat_transp,"Naive Transpose threads per block 512", 16,32);
TestCuda(&mat_transp, "Naive Transpose threads per block 512",32,16);
TestCuda(&mat_transp, "Naive Transpose threads per block 1024", 32,32);
TestCuda(&mat_fast_transp, "Optimized Transpose threads per block 64", 8,8);
TestCuda(&mat_fast_transp,"Optimized Transpose threads per blocks 512", 16,32);
TestCuda(&mat_fast_transp,"Optimized Transpose threads per block 512",32,16);
TestCuda(&mat_fast_transp,"Optimized Transpose threads per blocks 1024",32,32);

return 0;
}
