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
gcc blas_dmm.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_dmm.out
gcc blas_sdot.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_sdot.out
gcc blas_ddot.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_ddot.out
gcc blas_sscal.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_sscal.out
gcc blas_dscal.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_dscal.out
gcc blas_smv.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_smv.out
gcc blas_dgemv.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o blas_dgemv.out
gcc ssyev.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o ssyev.out
gcc dsyev.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o dsyev.out
gcc sgesvd.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o sgesvd.out
gcc dgesvd.c -I/home/deepikahv/binaries/openblas_v0.3.29/include -L/home/deepikahv/binaries/openblas_v0.3.29/lib -O3 -lopenblas -o dgesvd.out


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
echo "65536 65536 65536" |./sgemm.out
echo "65536 65536 65536" |./sgemm.out
echo "65536 65536 65536" |./sgemm.out



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
echo "65536 65536 65536" |./blas_dmm.out
echo "65536 65536 65536" |./blas_dmm.out
echo "65536 65536 65536" |./blas_dmm.out


echo "1024" | ./blas_sdot.out
echo "1024" | ./blas_sdot.out
echo "1024" | ./blas_sdot.out
echo "10240" | ./blas_sdot.out
echo "10240" | ./blas_sdot.out
echo "10240" | ./blas_sdot.out
echo "102400" | ./blas_sdot.out
echo "102400" | ./blas_sdot.out
echo "102400" | ./blas_sdot.out
echo "1024000" | ./blas_sdot.out
echo "1024000" | ./blas_sdot.out
echo "1024000" | ./blas_sdot.out
echo "10240000" | ./blas_sdot.out
echo "10240000" | ./blas_sdot.out
echo "10240000" | ./blas_sdot.out
echo "102400000" | ./blas_sdot.out
echo "102400000" | ./blas_sdot.out
echo "102400000" | ./blas_sdot.out

echo "1024" | ./blas_ddot.out
echo "1024" | ./blas_ddot.out
echo "1024" | ./blas_ddot.out
echo "10240" | ./blas_ddot.out
echo "10240" | ./blas_ddot.out
echo "10240" | ./blas_ddot.out
echo "102400" | ./blas_ddot.out
echo "102400" | ./blas_ddot.out
echo "102400" | ./blas_ddot.out
echo "1024000" | ./blas_ddot.out
echo "1024000" | ./blas_ddot.out
echo "1024000" | ./blas_ddot.out
echo "10240000" | ./blas_ddot.out
echo "10240000" | ./blas_ddot.out
echo "10240000" | ./blas_ddot.out
echo "102400000" | ./blas_ddot.out
echo "102400000" | ./blas_ddot.out
echo "102400000" | ./blas_ddot.out


echo "1024" | ./blas_sscal.out
echo "1024" | ./blas_sscal.out
echo "1024" | ./blas_sscal.out
echo "10240" | ./blas_sscal.out
echo "10240" | ./blas_sscal.out
echo "10240" | ./blas_sscal.out
echo "102400" | ./blas_sscal.out
echo "102400" | ./blas_sscal.out
echo "102400" | ./blas_sscal.out
echo "1024000" | ./blas_sscal.out
echo "1024000" | ./blas_sscal.out
echo "1024000" | ./blas_sscal.out
echo "10240000" | ./blas_sscal.out
echo "10240000" | ./blas_sscal.out
echo "10240000" | ./blas_sscal.out
echo "102400000" | ./blas_sscal.out
echo "102400000" | ./blas_sscal.out
echo "102400000" | ./blas_sscal.out

echo "1024" | ./blas_dscal.out
echo "1024" | ./blas_dscal.out
echo "1024" | ./blas_dscal.out
echo "10240" | ./blas_dscal.out
echo "10240" | ./blas_dscal.out
echo "10240" | ./blas_dscal.out
echo "102400" | ./blas_dscal.out
echo "102400" | ./blas_dscal.out
echo "102400" | ./blas_dscal.out
echo "1024000" | ./blas_dscal.out
echo "1024000" | ./blas_dscal.out
echo "1024000" | ./blas_dscal.out
echo "10240000" | ./blas_dscal.out
echo "10240000" | ./blas_dscal.out
echo "10240000" | ./blas_dscal.out
echo "102400000" | ./blas_dscal.out
echo "102400000" | ./blas_dscal.out
echo "102400000" | ./blas_dscal.out



cho "1024 1024 1024" |./blas_smv.out
echo "1024 1024 1024" |./blas_smv.out
echo "1024 1024 1024" |./blas_smv.out
echo "2048 2048 2048" |./blas_smv.out
echo "2048 2048 2048" |./blas_smv.out
echo "2048 2048 2048" |./blas_smv.out
echo "4096 4096 4096" |./blas_smv.out
echo "4096 4096 4096" |./blas_smv.out
echo "4096 4096 4096" |./blas_smv.out
echo "8192 8192 8192" |./blas_smv.out
echo "8192 8192 8192" |./blas_smv.out
echo "8192 8192 8192" |./blas_smv.out
echo "16384 16384 16384" |./blas_smv.out
echo "16384 16384 16384" |./blas_smv.out
echo "16384 16384 16384" |./blas_smv.out
echo "32768 32768 32768" |./blas_smv.out
echo "32768 32768 32768" |./blas_smv.out
echo "32768 32768 32768" |./blas_smv.out
echo "65536 65536 65536" |./blas_smv.out
echo "65536 65536 65536" |./blas_smv.out
echo "65536 65536 65536" |./blas_smv.out


echo "1024 1024 1024" |./blas_dgemv.out
echo "1024 1024 1024" |./blas_dgemv.out
echo "1024 1024 1024" |./blas_dgemv.out
echo "2048 2048 2048" |./blas_dgemv.out
echo "2048 2048 2048" |./blas_dgemv.out
echo "2048 2048 2048" |./blas_dgemv.out
echo "4096 4096 4096" |./blas_dgemv.out
echo "4096 4096 4096" |./blas_dgemv.out
echo "4096 4096 4096" |./blas_dgemv.out
echo "8192 8192 8192" |./blas_dgemv.out
echo "8192 8192 8192" |./blas_dgemv.out
echo "8192 8192 8192" |./blas_dgemv.out
echo "16384 16384 16384" |./blas_dgemv.out
echo "16384 16384 16384" |./blas_dgemv.out
echo "16384 16384 16384" |./blas_dgemv.out
echo "32768 32768 32768" |./blas_dgemv.out
echo "32768 32768 32768" |./blas_dgemv.out
echo "32768 32768 32768" |./blas_dgemv.out
echo "65536 65536 65536" |./blas_dgemv.out
echo "65536 65536 65536" |./blas_dgemv.out
echo "65536 65536 65536" |./blas_dgemv.out



echo "1024" | ./ssyev.out
echo "1024" | ./ssyev.out
echo "1024" | ./ssyev.out
echo "4096" | ./ssyev.out
echo "4096" | ./ssyev.out
echo "4096" | ./ssyev.out
echo "8192" | ./ssyev.out
echo "8192" | ./ssyev.out
echo "8192" | ./ssyev.out
echo "16384" | ./ssyev.out
echo "16384" | ./ssyev.out
echo "16384" | ./ssyev.out


echo "1024" | ./dsyev.out
echo "1024" | ./dsyev.out
echo "1024" | ./dsyev.out
echo "4096" | ./dsyev.out
echo "4096" | ./dsyev.out
echo "4096" | ./dsyev.out
echo "8192" | ./dsyev.out
echo "8192" | ./dsyev.out
echo "8192" | ./dsyev.out
echo "16384" | ./dsyev.out
echo "16384" | ./dsyev.out
echo "16384" | ./dsyev.out


echo "1024" | ./sgesvd.out
echo "1024" | ./sgesvd.out

echo "1024" | ./dgesvd.out
echo "1024" | ./dgesvd.out

echo "4096" | ./sgesvd.out
echo "4096" | ./dgesvd.out
