/// \file

#include <cstdint>
#include <iostream>
#include <atomic>

#include "data.hpp"
#include "scheduler.hpp"

/// Program entry point.
int32_t main() {
    std::vector<std::shared_ptr<Data>> data;
    data.emplace_back();
    auto d = std::make_shared<std::vector<std::shared_ptr<Data>>>(std::move(data));

    //scheduler::scheduler(d);
    dependency_scheduler::dependency_scheduler(d);


    return EXIT_SUCCESS;
}
