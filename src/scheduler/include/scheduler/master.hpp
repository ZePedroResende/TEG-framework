//
// Created by resende on 3/18/20.
//

#ifndef SCHEDULER_MASTER_HPP
#define SCHEDULER_MASTER_HPP

#include "queue.hpp"
#include "data.hpp"
#include "vector.hpp"

namespace scheduler {
    void master(const std::shared_ptr<::scheduler::Queue<int>> &q,
                const std::shared_ptr<::scheduler::Queue<int>> &r,
                const std::shared_ptr<DataVector> &data_vec
    );

}
#endif //SCHEDULER_MASTER_HPP
