//
// Created by resende on 4/2/20.
//

#ifndef DEPENDENCY_SCHEDULER_MASTER_HPP
#define DEPENDENCY_SCHEDULER_MASTER_HPP

#include <bits/shared_ptr.h>
#include <data.hpp>
#include "scheduler/queue.hpp"
#include "teg.h"
#include "teg_fn.hpp"

namespace dependency_scheduler {
    void master(const std::shared_ptr<scheduler::Queue<int>> &q,
                const std::shared_ptr<scheduler::Queue<int>> &r,
                const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec
    ) {

        static int initializer = 2;

        q->push(&initializer);

        while (!data_vec->empty()) {
            int *next = r->next();

            if (*next == TEG::FAIL) {
                data_vec->erase(data_vec->begin());

                *next = 2;
            }

            if (*next == TEG::SUCCESS) {
                std::cout << "TRUE\n";
                data_vec->erase(data_vec->begin());
                // save data
                *next = 2;
            }

            if (!data_vec->empty()) {
                q->push(next);
            }
        }
        q->stop();
    }
}

#endif //CLANG_BLUEPRINT_MASTER_HPP
