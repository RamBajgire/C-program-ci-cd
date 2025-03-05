#!/bin/bash
#SBATCH  -J gemm
#SBATCH  --nodes=1
#SBATCH  --time=02:00:00
#SBATCH --cpus-per-task=64
#SBATCH  --error=gemm_64_threads.err
#SBATCH  --output=gemm_64_threads.out
#SBATCH  --partition=picard
#SBATCH  --exclusive


ulimit -s unlimited

module load gcc/12.2

export LD_LIBRARY_PATH=/home/users/deepikahv/PICARD/build_dir/openblas_v0.3.29/lib/:$LD_LIBRARY_PATH


export OMP_NUM_THREADS=64
#export OPENBLAS_NUM_THREADS=48
echo "number of threads "
echo $OMP_NUM_THREADS
./nbody_omp.out
./nbody_omp.out
./nbody_omp.out
./nbody_omp.out
