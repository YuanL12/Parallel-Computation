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

    printf("\n");
    //define loop iterator variable outside parallel region
    int thread_id;

    #pragma omp parallel
    {
        thread_id = omp_get_thread_num();
        printf("there are %d threads\n", omp_get_max_threads());

        // create the loop to have each thread print hello.
        // each iteration will be randomly assigned to a different thread
        for(int i = 0; i < omp_get_max_threads(); i++){
            if(i == omp_get_thread_num()){
                printf("Hello from process: %d\n", thread_id);
            }
        }
        #pragma omp barrier
    }


    return 0;
}
