#!/bin/bash
#SBATCH -J testing
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --error=nbody_omp.err
#SBATCH --output=nbody_omp.out
#SBATCH --partition=picard
#SBATCH --exclusive
#module load gcc/11.2.0

cd /home/users/deepikahv/PICARD
source setup.sh


# Record start time in milliseconds
start_time=$(date +%s%3N)

# Execute the program
./nbody_omp

# Record end time in milliseconds
end_time=$(date +%s%3N)

# Calculate elapsed time in milliseconds
elapsed_time=$((end_time - start_time))

# Convert elapsed time to seconds and milliseconds
elapsed_sec=$((elapsed_time / 1000))
elapsed_millis=$((elapsed_time % 1000))

echo "Job finished in ${elapsed_sec} seconds and ${elapsed_millis} milliseconds"
