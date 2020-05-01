//
// Created by resende on 3/18/20.
//

#ifndef SCHEDULER_SLAVE_HPP
#define SCHEDULER_SLAVE_HPP

#include "scheduler/queue.hpp"
#include "data.hpp"
namespace scheduler {
    void slave(const std::shared_ptr<::scheduler::Queue<int>>& q,
               const std::shared_ptr<::scheduler::Queue<int>>& r,
               const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec) ;

}
#endif //CLANG_BLUEPRINT_SLAVE_HPP
