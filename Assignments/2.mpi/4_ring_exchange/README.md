# Distributed All-Reduce Sum of Vectors

## Task

In this exercise we implement and test, using MPI, the ring exchange communication
pattern. The method consists in each process first sending its datum to its successor
(identified by the communicator rank) and then receiving from its predecessor data and
forwarding what received to its successor.
Each process sends its data to the next one, receives data from its predecessor, sums it to its private data (sums are performed element-wise) and forwards to its successor what has received.
At the end, all the processes have the same values as data and print it to standard output.

The code has been optimized for sending in the ring a large set of data and overlapping the computation and the communication because this optimization makes the code much more efficient in terms of time.
