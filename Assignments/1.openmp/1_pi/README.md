The aim of this exercize is to approximate the value of Pi using the Montecarlo integral approximation.
## Procedure and Results:
I implemented the approximation algorithm in four different modes, as required by the assignment: 
a serial version, 
3 parallel versions using respectively the CRITICAL and ATOMIC directives and the REDUCTION clause.
All parallel versions are using OpenMP for multithreading.
I measured the execution time of all versions on a Ulysses node using 1, 2, 4, 8, 16 and 20 threads to see the scalability of my implementations,
with a problem size of 1'00'000'000 using the gcc compiler.
**Figure 1** show the results obtained through this procedure.
![Average execution time for Pi approximation](img/Graph_data_race _handlers.jpeg)
> Figure 1: Scalability of MonteCarlo integral approximation for different number of threads.

From the plot and the data it is evident that parallelizing the code leads to significant improvements in terms of execution time.
