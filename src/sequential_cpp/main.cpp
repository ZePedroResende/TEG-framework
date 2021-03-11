#include "data.hpp"  // Taskflow is header-only
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

void pipeline(std::vector<Data> &vector) {


  auto tbeg = std::chrono::steady_clock::now();

  for(Data &data: vector ){
    int ret = 2;
    while(ret > 1){
      ret = teg_fn(ret, &data);
    }
  }
  auto tend = std::chrono::steady_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tend - tbeg).count() << "\n";
}


int main(int argc, char *argv[]){
  //auto size = {1024};
  auto size = {32, 64, 128, 256, 512, 1024};
//  auto vector_size = {12, 24, 48, 96, 120, 240, 360, 600, 800, 1200, 2400, 4800, 9600};
  auto vector_size = {12, 24, 48, 96, 120, 240, 360, 600, 800, 1200, 2400, 4800, 9600, 12000};
  for(auto &i : size ){
    for(auto &j : vector_size){
      //if (!( i >= 512 && j > 1200)) {

      std::cout  << i << "-" << j << ", ";
      std::vector<Data> vec(j , Data(i));

      pipeline(vec);
      // }

    }
  }

  return 0;
}
