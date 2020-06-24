#include <sys/time.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "data.hpp"
#include "scheduler.hpp"
#include "vector.hpp"

//constexpr int data_size = 10000;
constexpr int data_size = 130;

/// Program entry point.
int main(int argc, char *argv[]) {
    std::shared_ptr<DataVector> d;

    d = std::make_shared<DataVector>(data_size);

    int TIME_RESOLUTION = 1000000;  // time measuring resolution (us)
    timeval t;
    gettimeofday(&t, NULL);
    long long unsigned initial_time = t.tv_sec * TIME_RESOLUTION + t.tv_usec;

    int n_threads = 2;
    if (argc > 1) {
        if (argc > 2) {
            n_threads = std::stoi(argv[2]);
        }
        if (!strcmp(argv[1], "1")) scheduler::normal_scheduler(d, n_threads);
        if (!strcmp(argv[1], "2")) dependency_scheduler::dependency_scheduler(d, n_threads);
        if (!strcmp(argv[1], "3"))
            dependency_scheduler_improved::dependency_scheduler_imp(d, n_threads);
        if (!strcmp(argv[1], "4")) {
            async_dependency_scheduler::dependency_scheduler_async(d, n_threads);
        }
    }

    gettimeofday(&t, NULL);
    long long unsigned final_time = t.tv_sec * TIME_RESOLUTION + t.tv_usec;

    std::cout << final_time - initial_time << "\n";

    return EXIT_SUCCESS;
}
