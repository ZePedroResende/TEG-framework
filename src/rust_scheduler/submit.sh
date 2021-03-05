#!/bin/sh
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run1
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run2
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run3
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run4
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run5
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run6
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run7
qsub -lnodes=1:r662:ppn=48,walltime=23:59:59 ./run8
