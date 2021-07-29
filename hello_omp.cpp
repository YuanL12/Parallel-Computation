#include<stdio.h>
#include<omp.h>

int main(int argc, char const *argv[])
{
    int id, nthreads;
    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        printf("Hello, OMP from thread %d\n", id);
        #pragma omp barrier
        if(id == 0){
            nthreads = omp_get_num_threads();
            printf("there are %d threads\n", nthreads);
        }
    }
    return 0;
}
