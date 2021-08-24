# Overview
This is a repository used to store personal learning process of OpenMP. OpenMP is a Compiler-side solution for creating code that runs on multiple cores/threads. I also listed some useful links I looked here.

In order to compile it 
### manually in **linux**, use the flag '-fopenmp'
```
g++ -o hello_omp.out hello_omp.cpp -fopenmp
```

### in **Mac**:
```
g++-10 -o hello_omp.out hello_omp.cpp -fopenmp
```

> **_Attention_**:
> If you use `g++ -o hello_omp.out hello_omp.cpp -fopenmp` in Mac, it will return an error like `clang: error: unsupported option '-fopenmp'`, and this is because g++ in Mac is default to use clang like `Apple clang version 12.0.0 (clang-1200.0.32.29)` in my case. You will need Homebrew to install GCC. The details of installation is listed below:
- Install gcc by Homebrew
```
brew install gcc
```
- Find the location of the newly installed gcc. Brew appends the version number to gcc so that it does not conflict with the one installed by Command Line Tools. You will find it in usr/local/bin. In my case it's usr/local/bin/gcc-10.

- Now you need to tell your system about it. When calling a compiler your bash will look into `/usr/bin` by default and not in `/usr/local/bin`. You need to add this directory to your `$PATH`. This can be easily done with the command:

```
vim ~/.zshrc
```
ann then change 
```
export PATH=/usr/local/bin:$PATH
```

### by **makefile** 
```
make hello_omp.out
./hello_omp.out
```

### in **RCC**
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
    /*-- Some work performed here --*/ 
    #pragma omp barrier // Correction: remove this barrier
}
work2(){
    /*-- Some work performed here --*/
}
main(){ 
    #pragma omp parallel sections 
    { 
        #pragma omp section
        work1(); 

        #pragma omp section
        work2();
    } // An implicit barrier
}
```
If executed by two threads, this program never finishes: Thread1 executing work1 waits forever in the explicit barrier, which thread2 will never encounter; Thread2 executing work2 waits forever in the implicit barrier at the end of the parallel sections construct, which thread1 will never encounter. *Note*: Do not insert a barrier that is not encountered by all threads of the same team.

- `#pragma omp master` defines a block of code that is guaranteed to be executed by the
master thread only. The master construct is often used (in combination with barrier construct) to initialize data, which is a preferable compared to the single construct


> **_Attention:_** 
> **Data race conditions** arise when multithreads read or write the same shared data simultaneously. It will not return the correct answer. Thus, we hope to update update a shared variable safely.

- `#pragma omp atomic` atomic structure  is applied only to the (single) assignment statement that immediately follows it. It will perform sequentially, and so there is performance penalty for using atomic, because the system coordinates all threads.  

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

The **critical** directive ensures that a line of code is only run by one process at a time, ensuring thread safety in the body of code. When a thread encounters a critical construct, it waits until no other thread is executing a critical region with the same name.

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
## Tutorial resoruces for OpenMP
https://www.bilibili.com/video/BV1964y127N9?from=search&seid=6613636337143045897
Cover some basic knowledge and visualization about the construction of cores/memomry. 

https://www.bu.edu/tech/files/2017/09/OpenMP_2017Fall.pdf provides a quick overview.

## Reduction Clause
https://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-reduction.html

## For loop and 'schedule' clause
http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
