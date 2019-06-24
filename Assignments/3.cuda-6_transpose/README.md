The purpose of the exercise is to implement a matrix transpose in CUDA that could abide to the blocking for cache approach to exploit GPU shared memory. We used a naive transpose function as baseline and both execution time (s) and bandwidth (GB/s) as metrics of performance, varying the block size (i.e. number of threads) to 64, 128, 256, 512 and 1024.

## Results

The original naive transpose algorithm using a thread block of the size of the tile (32x32) achieved a bandwidth of roughly 52.00 GB/s.

while the bandwidth results of execution are given by the improved version of the algorithm which is tuned to exploit blocking for cache in order to maximize the use of shared memory on the GPU.
```
Optimized Transpose threads per block 64: Correct
Time in milliseconds: 19.599903
Bandwidth: 54.783016 GB/s
-------------------
Optimized Transpose threads per blocks 512: Correct
Time in milliseconds: 13.200608
Bandwidth: 81.340328 GB/s
-------------------
Optimized Transpose threads per block 512: Correct
Time in milliseconds: 24.199455
Bandwidth: 44.370496 GB/s
-------------------
Optimized Transpose threads per blocks 1024: Correct
Time in milliseconds: 25.093472
Bandwidth: 42.789688 GB/s
```
