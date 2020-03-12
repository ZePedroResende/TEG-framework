#include "scheduler/queue.hpp"
#include <data.hpp>

namespace scheduler {
void master(const std::shared_ptr<scheduler::Queue<int>>& q,
            const std::shared_ptr<scheduler::Queue<int>>& r , const std::shared_ptr<std::vector<Data>>& data_vec) {

    static int initializer = 2;

    q->push(&initializer);

    while (!data_vec.get()->empty()){
        int* next = r->next();

        if (*next == 1) {
            data_vec->erase(data_vec->begin());
        }

        if (*next == 0) {
            //save data
        }
        q->push(next);
    }
}

}  // namespace scheduler
