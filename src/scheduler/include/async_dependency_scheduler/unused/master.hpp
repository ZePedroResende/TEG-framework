//
// Created by resende on 5/29/20.
//

#ifndef ASYNC_DEPENDENCY_SCHEDULER_MASTER_HPP
#define ASYNC_DEPENDENCY_SCHEDULER_MASTER_HPP

#include <atomic>
#include <set>
#include <utility>

#include "data.hpp"
#include "multiqueue.hpp"
#include "scheduler/queue.hpp"
#include "teg.h"
#include "teg_dependency.hpp"
#include "util.hpp"
#include "data_map.hpp"

#define MASTER_NUMBER 1
#define NUMBER_QUEUE 2

namespace async_dependency_scheduler {

    void master(const std::shared_ptr<Multiqueue<int>> &q,
                const std::shared_ptr<Multiqueue<std::pair<int, int>>> &r,
                const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec,
                int number_threads_pool) {

        auto data_map = DataMap(NUMBER_QUEUE, data_vec->size());
        auto cache = std::vector<std::map<int, int>>();

        for (int i = 0; i < NUMBER_QUEUE; i++) {
            cache.push_back(build_result_cache());
        }


        static int initializer = 2;

        int current = 2;
        int next = -1;

        auto deps = get_no_deps_fns(initializer);

        int division = deps.size() / number_threads_pool;
        int queues_to_be_used = division > NUMBER_QUEUE ? NUMBER_QUEUE : division;


        for (int i = 0; i < queues_to_be_used; i++) {
            for (auto &n : deps) {
                auto pair = std::make_pair(n, -2);
                update_cache(&cache[i], &pair);
                q->add_to_queue(i, n);
            }
            data_map.add_data_queue(i, i);
        }

        while (!data_map.is_finished()) {
            int queue_used = data_map.get_first_available();
            auto cache_used = cache[queue_used];

            std::pair<int, int> pair = r->get_from_queue(queue_used);

            update_cache(&cache_used, &pair);


            if (is_processed(&cache_used)) {

                // temos de calcular qual e o proximo
                next = get_next(current, &cache_used);
                current = next;

                if (next == TEG::FAIL) {
                    std::cout << "False\n";
                    data_map.terminate_data(queue_used);

                    next = 2;
                    cache[queue_used] = build_result_cache();
                    current = 2;
                }

                if (next == TEG::SUCCESS) {
                    std::cout << "TRUE\n";
                    data_map.terminate_data(queue_used);
                    // save data
                    next = 2;
                    cache[queue_used] = build_result_cache();
                    current = 2;
                }

                auto deps = get_no_deps_fns(initializer);

                int division = deps.size() / number_threads_pool;
                int queues_to_be_used = division > NUMBER_QUEUE ? NUMBER_QUEUE : division;


                for (auto &n : deps) {
                    auto pair = std::make_pair(n, -2);
                    update_cache(&cache[i], &pair);
                    q->add_to_queue(i, n);
                }

                data_map.add_data_queue(queue_used, data_map.get_latest() + 1);

                // Yoo vais ter que implementar uma estrutura que guarda o next e o current por queue
                // life sucks my friend i know ;/
                for (auto &n : get_no_deps_fns(next)) {
                    if (n != -2) {
                        int *n_ = new int(n);
                        q->push(n_);
                    }
                }

            } else {
                // Yoo vais ter que implementar uma estrutura que guarda o next e o current por queue
                // life sucks my friend i know ;/
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
