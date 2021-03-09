#include "taskflow/taskflow.hpp"  // Taskflow is header-only
#include "data.hpp"  // Taskflow is header-only
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

void pipeline(std::vector<Data> &vector) {


    auto tbeg = std::chrono::steady_clock::now();

    for(Data &data: vector ){

        tf::Executor executor;
        tf::Taskflow taskflow;
        auto [SUCESS, FAIL, Prop1, Prop2, Prop3, Prop4] = taskflow.emplace(  // create 4 tasks
                [] () {
                return 0;
                },
                [] () {
                return 1;
                },
                [&] () { return data.Prop1(); },
                [&] () { return data.Prop2(); },
                [&] () { return data.Prop3(); },
                [&] () { return data.Prop4(); }
                );

        SUCESS.succeed(Prop3,Prop4);
        FAIL.succeed(Prop1,Prop2);
        Prop1.precede(FAIL, Prop2,Prop3);
        Prop2.precede( FAIL,  Prop3, Prop4);
        Prop3.precede(SUCESS);
        Prop4.precede(SUCESS, FAIL);

        executor.run(taskflow).wait();

    }
    auto tend = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tend - tbeg).count() << "\n";
}


int main(int argc, char *argv[]){
    int element = std::atoi(argv[2]);
    int vector = std::atoi(argv[3]);
    auto size = {32, 64, 128, 256, 512, 1024};
    auto vector_size = {12, 24, 48, 96, 120, 240, 360, 600, 800, 1200, 2400, 4800, 9600, 12000};
    for(auto &i : size ){
        for(auto &j : vector_size){
            std::cout  << i << "-" << j << ", ";
            std::vector<Data> vec(j , Data(i));

            pipeline(vec);

        }
    }

    return 0;
}
