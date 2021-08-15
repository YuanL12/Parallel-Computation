# Overview
This is a repository used to store personal learning process of OpenMP. OpenMP is a Compiler-side solution for creating code that runs on multiple cores/threads. I also listed some useful links I looked here.

In order to compile it, use the flag '-fopenmp'
```
g++ -o hello.out hello_omp.cpp -fopenmp
```

## Introduction
- `omp_get_thread_num()` to obtain the thread id (non-negative integer) of the process. This will let us identify each of our threads using that unique id number.
- `omp_get_num_threads()` to obtain the total number of threads.

## A great general introduction for OpenMP
https://www.bilibili.com/video/BV1964y127N9?from=search&seid=6613636337143045897
Cover some basic knowledge and visualization about the construction of cores/memomry. 

## Reduction Clause
https://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-reduction.html

## For loop and 'schedule' clause
http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
