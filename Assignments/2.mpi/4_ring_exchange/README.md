# Distributed All-Reduce Sum of Vectors

## Task

Implement a communication pattern of all_reduce using non-blocking point to point communication, first exchanging one single element among processes. The code is optimized for sending in the ring a large set of data and overlapping the computation and the communication. In case of a dataset larger than one element the local sum is considered a vector sum (element by element).

For a large problem size (the parameter passed to the executable) using the overlapping communication is much more efficient in terms of time.
