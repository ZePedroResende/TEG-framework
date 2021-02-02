#!/bin/bash
source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64
module load cmake/3.10.0
cd $HOME/thesis/scheduler2/build/
rm -rf *
cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc -DCMAKE_Fortran_COMPILER=ifort -DCMAKE_BUILD_TYPE=Release ..
make
python ../run.py
