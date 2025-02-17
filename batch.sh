#!/bin/bash
#SBATCH -A username
#SBATCH -n 1
#SBATCH --nodelist=rvc24
#SBATCH --time=12:00:00
#SBATCH --exclusive
#SBATCH --output=output.out

export PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/bin:$PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LD_LIBRARY_PATH
export LIBRARY_PATH=/home/deepikahv/binaries/gcc_v12.2.0_inst_dir/lib:$LIBRARY_PATH
export LD_LIBRARY_PATH=/home/deepikahv/binaries/openblas_v0.3.29/lib/:$LD_LIBRARY_PATH
gcc sgemm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o sgemm.out
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

