//
// Created by resende on 3/19/20.
//

#ifndef CLANG_BLUEPRINT_SCHEDULER_HPP
#define CLANG_BLUEPRINT_SCHEDULER_HPP

#include "scheduler/master.hpp"
#include "scheduler/slave.hpp"
#include "scheduler/queue.hpp"

namespace scheduler {
    void scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec);
}
#endif //CLANG_BLUEPRINT_SCHEDULER_HPP
