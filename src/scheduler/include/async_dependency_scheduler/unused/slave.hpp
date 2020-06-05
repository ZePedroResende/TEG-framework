//
// Created by resende on 3/18/20.
//

#ifndef DEPENDENCY_SCHEDULER_IMPROVED_SLAVE_HPP
#define DEPENDENCY_SCHEDULER_IMPROVED_SLAVE_HPP

#include <logger.hpp>
#include <utility>

#include "data.hpp"
#include "scheduler/queue.hpp"
#include "teg_fn.hpp"
#include "multiqueue.hpp"

namespace async_dependency_scheduler {
    void slave(const std::shared_ptr<Multiqueue<int>>& q,
               const std::shared_ptr<Multiqueue<std::pair<int, int>>>& r,
               const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec, bool running) {
        while (running) {


            std::pair<int, int> next = q->get_first_queue();

            if (next.first != -1 ) {
                std::shared_ptr<Data> data = data_vec->at(next.first);
                // logger::instance().log(  "slave recived " + std::to_string(*next) );
                int integer = next.second;
                int ret = teg_fn(integer, data);
                // logger::instance().log(  "return " + std::to_string(ret ));
                // exec da funcao pegar no return next =
                std::pair<int,int> pair = std::make_pair(integer, ret);
                r->add_to_queue(next.first,pair);
            }
        }
    }
}  // namespace async_dependency_scheduler
#endif
