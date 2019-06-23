# Distributed Initialization of Identity Matrix

## Task

Implement a code to initialize a distributed identity matrix of size (N,N). Print the matrix ordered on standard output if N is smaller than 10, otherwise on a binary file. Implement the I/O overlapping the receiving data on process 0 with no-blocking communication, therefore overlapping I/O operations on disk with data echange between the processes.
