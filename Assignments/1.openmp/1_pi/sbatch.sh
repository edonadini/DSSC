#!/bin/bach
for i in 1 2 4 8 16 20;do
	printf "\nnthreads =${i}\n"
	export OMP_NUM_THREADS=${i}
	./approximate_pi
done
