#pragma once
#include "logger.hpp"
#include "multiqueue.hpp"
#include "teg_fn.hpp"

namespace async_dependency_scheduler {
void slave(const std::shared_ptr<Multiqueue>& queue,
           const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec) {
    while (!queue->is_terminated()) {
        DataFunction next = queue->next_to_process();
        if (next.has_data) {
            std::shared_ptr<Data> data = data_vec->at(next.data);
            logger::instance().log("slave recived data:" + std::to_string(next.data) +
                                   "function: " + std::to_string(next.function));
            int integer = next.function;
            int ret = teg_fn(integer, data);
            logger::instance().log("return " + std::to_string(ret));
            // exec da funcao pegar no return next =
            queue->set_output(next.data, next.function, ret);
        }
    }
}
}  // namespace async_dependency_scheduler
