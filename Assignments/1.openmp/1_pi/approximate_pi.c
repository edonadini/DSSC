#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

double f(double x)
{
	return 1/(1+x*x);
}

double local_sum(double local_a, double local_b, int local_n, double h){
	double local_result= 0.0;
	for(int i=0; i<=local_n-1;++i){
		double x_i=local_a +(i+0.5)*h;
		local_result +=f(x_i);
	};
	return local_result*4*h;
}

double serial(int n){
double h=1./n;
double res_s=local_sum(0,1,n,h); 
return res_s;
}

double atomic(int n){
double h=1./n;
double global_result_a=0.0;
	#pragma omp parallel
{
	int tid = omp_get_thread_num();
	int nthreads = omp_get_num_threads();

	int local_n = n/nthreads;
	double local_a = tid * local_n * h;
	double local_b = local_a + local_n * h;

	double local_result = local_sum(local_a, local_b, local_n, h);
	
	#pragma omp atomic
	global_result_a +=local_result;
}
return global_result_a;
};
	

double critical(int n){	
double h=1./n;
double global_result_c=0.0;
#pragma omp parallel
{
	int tid = omp_get_thread_num();
	int nthreads = omp_get_num_threads();

	int local_n = n/nthreads;
	double local_a = tid * local_n * h;
	double local_b = local_a + local_n * h;

	double local_result=local_sum(local_a,local_b,local_n,h); 
	#pragma omp critical
	global_result_c +=local_result;
}
return global_result_c;
};


double reduction(int n){
double h=1./n;
double global_result_r=0.0;	
#pragma omp parallel reduction(+:global_result_r)
{
	int tid = omp_get_thread_num();
	int nthreads = omp_get_num_threads();

	int local_n = n/nthreads;
	double local_a = tid * local_n * h;
	double local_b = local_a + local_n * h;
 
	global_result_r +=local_sum(local_a,local_b, local_n, h);
}
return global_result_r;
};

	
int main (int argc, char *argv[]){

int n=100000000;
double global_result_a=atomic(n);
double global_result_c=critical(n);
double global_result_r=reduction(n);
double serial_result=serial(n);

double a=omp_get_wtime();
atomic(n);	
double duration_atomic= omp_get_wtime()-a;
double c=omp_get_wtime();
critical(n);
double duration_critical= omp_get_wtime()-c;
double r=omp_get_wtime();	
reduction(n);
double duration_reduction= omp_get_wtime()-r;
double s=omp_get_wtime();
serial(n);
double serial_duration=omp_get_wtime()-s;
	
printf("For atomic section pi=%f, time=%f\n",global_result_a, duration_atomic);
printf("For critical section pi=%f, time=%f\n",global_result_c, duration_critical);
printf("For reduction section pi=%f, time=%f\n",global_result_r, duration_reduction);
printf("For the serial computation pi=%f, time=%f\n",serial_result, serial_duration);
return 0;
}

