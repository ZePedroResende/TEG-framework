//
// Created by resende on 3/18/20.
//

#ifndef DEPENDENCY_SCHEDULER_SLAVE_HPP
#define DEPENDENCY_SCHEDULER_SLAVE_HPP

#include "scheduler/queue.hpp"
#include "data.hpp"
#include <utility>
#include <teg_fn.hpp>

namespace dependency_scheduler {
    void slave(const std::shared_ptr<scheduler::Queue<int>> &q,
               const std::shared_ptr<scheduler::Queue<std::pair<int, int>>> &r,
               const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {
        while (!data_vec->empty()) {
            auto data = data_vec->front();

            //locked threads quando as outras acabam !

            int *next = q->next();

            if (next != nullptr) {

                std::cout << "slave recived " << *next << '\n';
                int integer = *next;
                int ret = teg_fn(integer, data);
                std::cout << "return " << ret << '\n';
                // exec da funcao pegar no return next =
                auto pair = std::make_pair(integer, ret);
                r->push(&pair);
            }
        }

    }
}
#endif
