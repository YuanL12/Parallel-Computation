# Overview
This is a repository used to store personal learning process of OpenMP. OpenMP is a Compiler-side solution for creating code that runs on multiple cores/threads. I also listed some useful links I looked here.

In order to compile it manually, use the flag '-fopenmp'
```
g++ -o hello_omp.out hello_omp.cpp -fopenmp
```

or by makefile 
```
make hello_omp.out
./hello_omp.out
```

or in RCC
```
sbatch ./run.sbatch
```



## Notes of OpenMP
- `omp_get_thread_num()` to obtain the thread id (non-negative integer) of the process. This will let us identify each of our threads using that unique id number.
- `omp_get_num_threads()` to obtain the total number of threads.
- `#pragma omp shared(shar_Var1) private(priv_Var1, priv_Var2)` to indicate private or shared variable, declare the variable before your parallel section and annotate the pragma omp directive.
- `private(id)` used to create a separate instance of identical for each task.

- `omp_get_max_threads()` to retrieve the max thread count.
- `#pragma omp section` The work in each section must be independent and each section is distributed to one thread to run. 
```C++
#pragma omp sections [clause[[,] clause]. . . ]
{
    [#pragma omp section ]
    …… code block 1 ......
    [#pragma omp section
    …… code block 2 ...... ]
    . . .
}
```
- `#pragma omp single` The code block following the single construct is executed by one thread only and the other threads wait at a barrier until the executing thread has completed. The executing thread could be any thread (not necessary the master one). Useful for initializing variables, otherwise multiple threads will assign the value to a variable at the same time, potentially resulting in a memory problem.
- `#pragma omp barrier` Threads wait for each other at a barrier. No thread may proceed beyond a barrier until all threads in the team have reached the barrier. **TAKE CARE**:  Illegal use of the barrie can cause **dead lock** 
```C++
work1(){
/*-- Some work performed here --*/ #pragma omp barrier // Correction: remove this barrier
}
work2(){
/*-- Some work performed here --*/
}
main(){ #pragma omp parallel sections 
{ #pragma omp section
work1(); #pragma omp section
work2();
} // An implicit barrier
}
```

### Barrier and Critical Directives 
Used to managing processes:
``` C++
#pragma omp barrier
```
, and the critical directives:
```C++
#pragma omp critical { … }
```

The **barrier** directive stops all processes for proceeding to the next line of code until all processes have reached the barrier, to ensure one process doesn’t get ahead of another. This allows a programmer to **synchronize** sequences in the parallel process.

The **critical** directive ensures that a line of code is only run by one process at a time, ensuring thread safety in the body of code.

### Work Sharing Directive: omp for
The directive omp for divides a normally serial for loop into a parallel task. Syntax:
```C++
#pragma omp for { … }
```
The code before and after the loop is executed identically in each thread; the loop iterations are spread over the four threads.

**Example**
We will use the `#pragma omp for` to declare the loop as to be work sharing, followed by the actual C++ loop. 
```C++
#pragma omp for
for(int i = 1; i <= 1000; i++){
    partial_Sum += i;
}
```


Next we must join our threads. To do this we must use a critical directive to create a thread safe section of code. We do this with `#pragma omp critical` directive. Lastly we add partial sum to total sum and print out the result outside the parallel section of code.
```C++
    // Create thread safe region.
    #pragma omp critical
    {
        //add each threads partial sum to the total sum
        total_Sum += partial_Sum;
    }
```
## A great general introduction for OpenMP
https://www.bilibili.com/video/BV1964y127N9?from=search&seid=6613636337143045897
Cover some basic knowledge and visualization about the construction of cores/memomry. 

https://www.bu.edu/tech/files/2017/09/OpenMP_2017Fall.pdf

## Reduction Clause
https://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-reduction.html

## For loop and 'schedule' clause
http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
