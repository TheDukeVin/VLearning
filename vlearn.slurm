#!/bin/bash
#SBATCH -c 1 # Number of cores requested
#SBATCH -t 1000 # Runtime in minutes
#SBATCH -p shared # Partition to submit to
#SBATCH --mem=3000 # Memory per node in MB (see also --mem-per-cpu)
#SBATCH -o vlearn_std.out # Standard out goes to this file
#SBATCH -e vlearn_std.err # Standard err goes to this filehostname
srun -l a.out