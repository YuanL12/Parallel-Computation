#!/bin/bash

#SBATCH --job-name=omp_hello
#SBATCH --account=pi-bradnelson
#SBATCH --output=sbatch.out
#SBATCH --error=sbatch.err
#SBATCH --time=0:01:00
#SBATCH --nodes=1
#SBATCH --partition=caslake
#SBATCH --ntasks-per-node=1 # number of tasks
#SBATCH --cpus-per-task=5  # number of threads

module load gcc

# DO COMPUTE WORK
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./maximum.out