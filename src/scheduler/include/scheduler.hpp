//
// Created by resende on 3/19/20.
//

#ifndef CLANG_BLUEPRINT_SCHEDULER_HPP
#define CLANG_BLUEPRINT_SCHEDULER_HPP

#include "scheduler/master.hpp"
#include "scheduler/slave.hpp"
#include "scheduler/queue.hpp"


namespace scheduler {

    void normal_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec, int n_threads);
}

namespace dependency_scheduler {
    void dependency_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec, int n_threads);
}


namespace dependency_scheduler_improved {
    void dependency_scheduler_imp(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec, int n_threads);
}

namespace async_dependency_scheduler {
    void dependency_scheduler_async(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec, int n_threads);
}
#endif //CLANG_BLUEPRINT_SCHEDULER_HPP
