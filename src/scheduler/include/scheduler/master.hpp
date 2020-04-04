//
// Created by resende on 3/18/20.
//

#ifndef SCHEDULER_MASTER_HPP
#define SCHEDULER_MASTER_HPP

#include "queue.hpp"
#include "data.hpp"

namespace scheduler {
    void master(const std::shared_ptr<scheduler::Queue<int>> &q,
                const std::shared_ptr<scheduler::Queue<int>> &r,
                const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec
    );

}
#endif //SCHEDULER_MASTER_HPP
