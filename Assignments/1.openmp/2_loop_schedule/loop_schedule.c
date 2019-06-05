#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


void print_usage( int * a, int N, int nthreads ) {

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

int main( int argc, char * argv[] ) {

	const int N = 250;
	int a[N];
	int i;

	int num_threads = argc>=2 ? atoi(argv[1]) : 4;
	//int thread_id =0;
	//int nthreads =1;

	//for(int i=0; i<N; ++i) {
	//a[i] = thread_id;
	//}	
	//print_usage(a,N,nthreads);                                                                                                                       
	#pragma omp parallel for schedule (dynamic,1) private(i)
		for (i=0; i<N; ++i) {
		a[i] = omp_get_thread_num();
	}	
	print_usage(a,N,num_threads);
	//printf("Num thread = %d\n",num_threads);		

  return 0;
}

