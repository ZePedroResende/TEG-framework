#!/bin/bash
source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64
module load cmake/3.10.0
cd $HOME/thesis/scheduler/build/
python run.py
