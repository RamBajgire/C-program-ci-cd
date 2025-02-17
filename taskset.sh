#!/bin/bash
#SBATCH -A username
#SBATCH -n 1
#SBATCH --nodelist=rvc24
#SBATCH --time=12:00:00
#SBATCH --exclusive
#SBATCH --output=output_taskset.out
#SBATCH --error=error

export PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/bin:$PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LD_LIBRARY_PATH
export LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/openblas_v0.3.29/lib/:$LD_LIBRARY_PATH

export OMP_NUM_THREADS=64
export OMP_PLACES=cores
export OMP_PROC_BIND=spread
gcc sgemm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o sgemm.out
gcc blas_dmm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_dmm.out


echo "sgemm"
echo " "
echo "1024 1024 1024" |taskset -c 0-64 ./sgemm.out
echo "1024 1024 1024" |taskset -c 0-64 ./sgemm.out
echo "2048 2048 2048" |taskset -c 0-64 ./sgemm.out
echo "2048 2048 2048" |taskset -c 0-64 ./sgemm.out
echo "4096 4096 4096" |taskset -c 0-64 ./sgemm.out
echo "4096 4096 4096" |taskset -c 0-64 ./sgemm.out
echo "8192 8192 8192" |taskset -c 0-64 ./sgemm.out
echo "8192 8192 8192" |taskset -c 0-64 ./sgemm.out
echo "16384 16384 16384" |taskset -c 0-64 ./sgemm.out
echo "32768 32768 32768"  |taskset -c 0-64 ./sgemm.out



echo "blas_dmm"
echo " "
echo "1024 1024 1024" |taskset -c 0-64 ./blas_dmm.out
echo "1024 1024 1024" |taskset -c 0-64 ./blas_dmm.out
echo "2048 2048 2048" |taskset -c 0-64 ./blas_dmm.out
echo "2048 2048 2048" |taskset -c 0-64 ./blas_dmm.out
echo "4096 4096 4096" |taskset -c 0-64 ./blas_dmm.out
echo "4096 4096 4096" |taskset -c 0-64 ./blas_dmm.out
echo "8192 8192 8192" |taskset -c 0-64 ./blas_dmm.out
echo "8192 8192 8192" |taskset -c 0-64 ./blas_dmm.out
echo "16384 16384 16384" |taskset -c 0-64 ./blas_dmm.out
echo "32768 32768 32768" |taskset -c 0-64 ./blas_dmm.out
