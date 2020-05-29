#ifndef ASYNC_DEPENDENCY_SCHEDULER_SLAVE_HPP
#define ASYNC_DEPENDENCY_SCHEDULER_SLAVE_HPP

#include <logger.hpp>
#include <utility>

#include "data.hpp"
#include "scheduler/queue.hpp"
#include "teg_fn.hpp"
namespace async_dependency_scheduler {
void slave(const std::shared_ptr<scheduler::Queue<int>>& q,
           const std::shared_ptr<scheduler::Queue<std::pair<int, int>>>& r,
           const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec, bool running) {
    while (running) {
        // locked threads quando as outras acabam !
        // q->print_queue();
        int* next = q->next();

        auto data = data_vec->front();

        if (next != nullptr) {
            // logger::instance().log(  "slave recived " + std::to_string(*next) );
            int integer = *next;
            int ret = teg_fn(integer, data);
            // logger::instance().log(  "return " + std::to_string(ret ));
            // exec da funcao pegar no return next =
            auto pair = std::make_pair(integer, ret);
            r->push(&pair);
        }
    }
}
}  // namespace async_dependency_scheduler
#endif
