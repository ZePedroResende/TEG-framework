#include "scheduler/queue.hpp"
namespace scheduler {
void master(const std::shared_ptr<scheduler::Queue<int>>& q,
            const std::shared_ptr<scheduler::Queue<int>>& r) {
    static int initializer = 2;
    q->push(&initializer);
    for (;;) {
        int* next = r->next();

        if (*next == 1) {
            // error
            // next data

            return;
        }

        if (*next == 0) {
            // sucess
            return;
        }
        q->push(next);
    }
}

}  // namespace scheduler
