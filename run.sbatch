#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=0:01:00
#SBATCH --partition=shas-testing
#SBATCH --ntasks=4
#SBATCH --job-name=omp_hello
#SBATCH --output=sbatch.out


./hello_omp.out