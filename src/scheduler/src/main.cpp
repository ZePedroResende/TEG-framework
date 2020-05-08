/// \file

#include <atomic>
#include <cstdint>
#include <iostream>

#include "data.hpp"
#include "scheduler.hpp"

/// Program entry point.
int32_t main() {
    auto d1 = std::make_shared<Data>(Data());
    auto data = std::vector<std::shared_ptr<Data>>();

    data.push_back(d1);

    auto d = std::make_shared<std::vector<std::shared_ptr<Data>>>(std::move(data));

    // scheduler::normal_scheduler(d);
    // dependency_scheduler::dependency_scheduler(d);
    dependency_scheduler_improved::dependency_scheduler_imp(d);

    return EXIT_SUCCESS;
}
