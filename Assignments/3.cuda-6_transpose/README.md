The purpose of the exercise is to implement a matrix transpose in CUDA that could abide to the blocking for cache approach to exploit GPU shared memory. We used a naive transpose function as baseline and both execution time (s) and bandwidth (GB/s) as metrics of performance, varying the block size (i.e. number of threads) to 64, 128, 256, 512 and 1024.

## Results

```
-------------------
Naive Transpose threads per block 64: Correct
Time in milliseconds: 10585.202148
Bandwidth: 0.101438 GB/s
-------------------
Naive Transpose threads per block 512: Correct
Time in milliseconds: 3810.392334
Bandwidth: 0.281793 GB/s
-------------------
Naive Transpose threads per block 512: Correct
Time in milliseconds: 9413.301758
Bandwidth: 0.114066 GB/s
-------------------
Naive Transpose threads per block 1024: Correct
Time in milliseconds: 5358.452637
Bandwidth: 0.200383 GB/s
-------------------
Optimized Transpose threads per block 64: Correct
Time in milliseconds: 16.293633
Bandwidth: 65.899476 GB/s
-------------------
Optimized Transpose threads per blocks 512: Correct
Time in milliseconds: 9.420992
Bandwidth: 113.973328 GB/s
-------------------
Optimized Transpose threads per block 512: Correct
Time in milliseconds: 16.960064
Bandwidth: 63.310012 GB/s
-------------------
Optimized Transpose threads per blocks 1024: Correct
Time in milliseconds: 17.003424
Bandwidth: 63.148568 GB/s
-------------------

```
