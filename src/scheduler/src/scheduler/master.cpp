#include <teg.h>

#include <atomic>

#include "data.hpp"
#include "scheduler/queue.hpp"
#include "vector.hpp"

namespace scheduler {
    void master(const std::shared_ptr<scheduler::Queue<int>> &q,
                const std::shared_ptr<scheduler::Queue<int>> &r,
                const std::shared_ptr<DataVector> &data_vec) {
        static int initializer = 2;

        q->push(initializer);

        while (!data_vec->empty()) {
            int next = r->next();

            if (next == TEG::FAIL) {
                data_vec->erase();

                next = 2;
            }

            if (next == TEG::SUCCESS) {
                //std::cout << "TRUE\n";
                data_vec->erase();
                // save data
                next = 2;
            }

            if (!data_vec->empty()) {
                q->push(next);
            }
        }
        q->stop();
    }

}  // namespace scheduler
