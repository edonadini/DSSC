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
Time in milliseconds: 19.577856
Bandwidth: 54.844708 GB/s
-------------------
Optimized Transpose threads per blocks 512: Correct
Time in milliseconds: 13.285888
Bandwidth: 80.818224 GB/s
-------------------
Optimized Transpose threads per block 512: Correct
Time in milliseconds: 24.196417
Bandwidth: 44.376068 GB/s
-------------------
Optimized Transpose threads per blocks 1024: Correct
Time in milliseconds: 25.163937
Bandwidth: 42.669868 GB/s
-------------------

```
