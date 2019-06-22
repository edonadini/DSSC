#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define N 250


void print_usage( int * a, int nthreads ) {

  int tid, i;
  for( tid = 0; tid < nthreads; ++tid ) {

    fprintf( stdout, "%d: ", tid );

    for( i = 0; i < N; ++i ) {

      if( a[ i ] == tid) fprintf( stdout, "*" );
      else fprintf( stdout, " ");
    }
    printf("\n");
  }
}

void serial_e(int *a)
{
	int thread_id=0;
	int num_threads=1;
	for(int i=0;i<N;++i)
	{
		a[i] =thread_id;
	}
printf("serial:\n");
print_usage(a,num_threads);
}

void static_e(int *a)
{
	int num_threads=10;
	int i;
	#pragma omp parallel private(i)
	{
		int thread_id=omp_get_thread_num(); 
		#pragma omp for schedule (static)
			for (i=0; i<N; ++i)
			{
			a[i] = thread_id;
			}
	}
	printf("schedule static:\n");	
	print_usage(a,num_threads);
}


void static_e_chunk(int *a,int chunk_s)
{
	int num_threads=10;
	int i;
	#pragma omp parallel private(i)
	{
		int thread_id=omp_get_thread_num(); 
		#pragma omp for schedule (static,chunk_s)
			for (i=0; i<N; ++i)
			{
			a[i] = thread_id;
			}
	}
	printf("schedule static %d:\n", chunk_s);	
	print_usage(a,num_threads);
}
		
void dynamic_e(int *a)
{
	int num_threads=10;
	int i;
	#pragma omp parallel private(i)
	{
		int thread_id=omp_get_thread_num(); 
		#pragma omp for schedule (dynamic)
			for (i=0; i<N; ++i)
			{
			a[i] = thread_id;
			}
	}
	printf("schedule dynimic:\n");	
	print_usage(a,num_threads);
}
void dynamic_e_chunk(int *a, int chunk_s)
{
	int num_threads=10;
	int i;
	#pragma omp parallel private(i)
	{
		int thread_id=omp_get_thread_num(); 
		#pragma omp for schedule (dynamic, chunk_s)
			for (i=0; i<N; ++i)
			{
			a[i] = thread_id;
			}
	}
	printf("schedule dynamic %d:\n", chunk_s);	
	print_usage(a,num_threads);
}
int main( int argc, char * argv[] ) {

	int a[N];
                                                                                                                    
	serial_e(a);
	static_e(a);
	static_e_chunk(a,1);
	static_e_chunk(a,10);
	dynamic_e(a);
	dynamic_e_chunk(a,1);
	dynamic_e_chunk(a,10);
  return 0;
}

