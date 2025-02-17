#!/bin/bash
#SBATCH --j test
#SBATCH -n 1
#SBATCH --nodelist=rvc24
#SBATCH --time=12:00:00
#SBATCH --cpus-per-task=64
#SBATCH --exclusive
#SBATCH --output=output_cpu_bind_true_omp_src.out
#SBATCH --error=error

export PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/bin:$PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LD_LIBRARY_PATH
export LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/openblas_v0.3.29/lib/:$LD_LIBRARY_PATH
source /home/deepikahv/binaries/set_vars.sh
g++ pi_omp.cpp -fopenmp -O3 -o pi_omp
g++ convolution_omp.cpp -fopenmp -O3 -o convolution_omp
g++ brutforce_nbody/nbody_omp.cpp -fopenmp -O3 -o nbody_omp
g++ sparse_mm.cpp -fopenmp -O3 -o sparse_mm
g++ laplace.cpp -fopenmp -O3 -o laplace.out
ulimit -s unlimited

export OMP_NUM_THREADS=64
export OMP_PLACES=cores
export OMP_PROC_BIND=true

echo "pi cal"
./pi_omp 10000384
./pi_omp 10000384
./pi_omp 10000384
./pi_omp 10000384
echo " "
echo "convolution"
echo " "
./convolution_omp 8192 8192
./convolution_omp 8192 8192
./convolution_omp 8192 8192
./convolution_omp 8192 8192
echo " "
echo "nbody "
echo " "
./nbody_omp 
./nbody_omp
./nbody_omp
./nbody_omp
echo " "
echo "sparse_mm "
echo " "
./sparse_mm
./sparse_mm
./sparse_mm
./sparse_mm

echo "laplace size: nodes:  51200   Elements: 102400"
echo ""
./laplace.out 51200 102400
./laplace.out  51200 102400
./laplace.out  51200 102400
./laplace.out  51200 102400
