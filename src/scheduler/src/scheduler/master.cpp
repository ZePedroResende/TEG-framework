#include <teg.h>

#include <atomic>

#include "data.hpp"
#include "scheduler/queue.hpp"

namespace scheduler {
void master(const std::shared_ptr<scheduler::Queue<int>>& q,
            const std::shared_ptr<scheduler::Queue<int>>& r,
            const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec) {
    static int initializer = 2;

    q->push(&initializer);

    while (!data_vec->empty()) {
        int* next = r->next();

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

}  // namespace scheduler
