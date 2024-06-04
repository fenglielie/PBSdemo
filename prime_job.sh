#!/bin/bash

# name
#PBS -N prime_job

# output
#PBS -o out_$PBS_JOBID
#PBS -j oe

# resource
#PBS -l nodes=1:ppn=4
#PBS -l walltime=24000:00:00

# queue
#PBS -q cu2

# retry
#PBS -r y

# export all environment variables
#PBS -V


# information
echo ------------------------------------------------------
echo [PBS] job id: $PBS_JOBID
echo [PBS] job name: $PBS_JOBNAME
echo [PBS] executing queue: $PBS_QUEUE
echo [PBS] working directory: $PBS_O_WORKDIR/PBS_$PBS_JOBID
echo [PBS] home directory: $PBS_O_HOME
echo ------------------------------------------------------

# directory
cd $PBS_O_WORKDIR
mkdir PBS_$PBS_JOBID
cd PBS_$PBS_JOBID

date

$PBS_O_WORKDIR/prime

date
