#include <sys/time.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <iostream>

#include "data.hpp"
#include "scheduler.hpp"

/// Program entry point.
int main(int argc, char *argv[]) {
    auto data = std::vector<std::shared_ptr<Data>>();
    for (int i = 0; i < 1000; i++) {
        auto d1 = std::make_shared<Data>(Data());
        data.push_back(d1);
    }

    auto d = std::make_shared<std::vector<std::shared_ptr<Data>>>(std::move(data));

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
        if (!strcmp(argv[1], "3")) dependency_scheduler_improved::dependency_scheduler_imp(d, n_threads);
        if (!strcmp(argv[1], "4")) async_dependency_scheduler::dependency_scheduler_async(d, n_threads);
    }

    gettimeofday(&t, NULL);
    long long unsigned final_time = t.tv_sec * TIME_RESOLUTION + t.tv_usec;

    std::cout << final_time - initial_time << "\n";

    return EXIT_SUCCESS;
}
