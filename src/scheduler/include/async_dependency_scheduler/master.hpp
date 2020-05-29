//
// Created by resende on 4/26/20.
//

#ifndef DEPENDENCY_SCHEDULER_IMPROVED_MASTER_HPP
#define DEPENDENCY_SCHEDULER_IMPROVED_MASTER_HPP

#include <atomic>
#include <set>
#include <utility>

#include "data.hpp"
#include "scheduler/queue.hpp"
#include "teg.h"
#include "teg_dependency.hpp"
#include "util.hpp"

namespace async_dependency_scheduler {

void master(const std::shared_ptr<scheduler::Queue<int>>& q,
            const std::shared_ptr<scheduler::Queue<std::pair<int, int>>>& r,
            const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec) {
    auto cache = build_result_cache();

    auto next_up = std::queue<int>();

    static int initializer = 2;

    int current = 2;
    int next = -1;

    for (auto& n : get_no_deps_fns(initializer)) {
        auto pair = std::make_pair(n, -2);
        update_cache(&cache, &pair);
        int* n_ = new int(n);
        q->push(n_);
    }

    while (!data_vec->empty()) {
        std::pair<int, int>* pair = r->next();
        update_cache(&cache, pair);
        // E necessario adicionar os que ja estao a ser processados
        if (is_processed(&cache)) {
            // temos de calcular qual e o proximo
            next = get_next(current, &cache);
            current = next;

            if (next == TEG::FAIL) {
                // std::cout << "False\n";
                data_vec->erase(data_vec->begin());

                next = 2;
            }

            if (next == TEG::SUCCESS) {
                // std::cout << "TRUE\n";
                data_vec->erase(data_vec->begin());
                // save data
                next = 2;
                cache = build_result_cache();
                current = 2;
            }

            if (!data_vec->empty()) {
                for (auto& n : get_no_deps_fns(next)) {
                    if (n != -2) {
                        int* n_ = new int(n);
                        q->push(n_);
                    }
                }
            }

        } else {
            if (current == pair->first) {
                next = get_next(current, &cache);
                current = next;
            }
        }
    }
    q->stop();
}  // namespace dependency_scheduler
}  // namespace async_dependency_scheduler
#endif  // TEG_MASTER_HPP
