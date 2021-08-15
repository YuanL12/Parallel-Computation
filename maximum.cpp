#include <stdio.h>
#include <omp.h>
#include <vector>

int main(int argc, char** argv){
    std::vector<int> v = {2,3,4,1,7,4,4};

    int partial_max, total_max;

    #pragma omp parallel private(partial_max) shared(total_max, v)
    {
        partial_max = v[0];
        total_max = v[0];

        // shared work by each thread
        #pragma omp for
        for(int i = 1; i < v.size() ; i++){
            if(v[i] > partial_max) partial_max = v[i];
        }

        // Create thread safe region.
        // critical: Specifies that code is only executed on one thread at a time.
        #pragma omp critical
        {
            //compare each thread's partial maximum to the total maximum
            if(total_max < partial_max) total_max = partial_max;
        }
    }
    printf("Max = %d\n", total_max);
    return 0;
}