#!/bin/bash
#SBATCH -A username
#SBATCH -n 1
#SBATCH --nodelist=rvc25
#SBATCH --time=12:00:00
#SBATCH --exclusive
#SBATCH --output=output_omp.out
#SBATCH --error=error

export PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/bin:$PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LD_LIBRARY_PATH
export LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/openblas_v0.3.29/lib/:$LD_LIBRARY_PATH

export OMP_NUM_THREADS=64
gcc sgemm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o sgemm.out
gcc blas_dmm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_dmm.out


echo "sgemm"
echo " "
echo "1024 1024 1024" |./sgemm.out
echo "1024 1024 1024" |./sgemm.out
echo "1024 1024 1024" |./sgemm.out
echo "2048 2048 2048" |./sgemm.out
echo "2048 2048 2048" |./sgemm.out
echo "2048 2048 2048" |./sgemm.out
echo "4096 4096 4096" |./sgemm.out
echo "4096 4096 4096" |./sgemm.out
echo "4096 4096 4096" |./sgemm.out
echo "8192 8192 8192" |./sgemm.out
echo "8192 8192 8192" |./sgemm.out
echo "8192 8192 8192" |./sgemm.out
echo "16384 16384 16384" |./sgemm.out
echo "16384 16384 16384" |./sgemm.out
echo "16384 16384 16384" |./sgemm.out
echo "32768 32768 32768" |./sgemm.out
echo "32768 32768 32768" |./sgemm.out
echo "32768 32768 32768" |./sgemm.out



echo "blas_dmm"
echo " "
echo "1024 1024 1024" |./blas_dmm.out
echo "1024 1024 1024" |./blas_dmm.out
echo "1024 1024 1024" |./blas_dmm.out
echo "2048 2048 2048" |./blas_dmm.out
echo "2048 2048 2048" |./blas_dmm.out
echo "2048 2048 2048" |./blas_dmm.out
echo "4096 4096 4096" |./blas_dmm.out
echo "4096 4096 4096" |./blas_dmm.out
echo "4096 4096 4096" |./blas_dmm.out
echo "8192 8192 8192" |./blas_dmm.out
echo "8192 8192 8192" |./blas_dmm.out
echo "8192 8192 8192" |./blas_dmm.out
echo "16384 16384 16384" |./blas_dmm.out
echo "16384 16384 16384" |./blas_dmm.out
echo "16384 16384 16384" |./blas_dmm.out
echo "32768 32768 32768" |./blas_dmm.out
echo "32768 32768 32768" |./blas_dmm.out
echo "32768 32768 32768" |./blas_dmm.out
