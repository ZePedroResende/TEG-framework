#!/bin/bash
source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64
module load cmake/3.1.0
cd $HOME/scheduler_new/build/
python testing.py
