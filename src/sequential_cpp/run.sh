#!/bin/bash
module load gcc/5.3.0
source /share/apps/intel/parallel_studio_xe_2020/compilers_and_libraries_2020/linux/bin/compilervars.sh intel64
cd $HOME/taskflow
make clean
make
# -std=c++17 main.cpp teg.h data.cpp data.hpp -I/home/resende/Developer/msc-thesis/src/taskflow/taskflow -O3 -pthread -o main  
