#include <data.hpp>

#include "scheduler/queue.hpp"
#include "teg_fn.hpp"
#include "vector.hpp"

namespace scheduler {
    void slave(const std::shared_ptr<scheduler::Queue<int>> &q,
               const std::shared_ptr<scheduler::Queue<int>> &r,
               const std::shared_ptr<DataVector> &data_vec) {
        while (!data_vec->empty()) {
            auto data = data_vec->front();
            if (data != nullptr){

                // locked threads quando as outras acabam !
                int next = q->next();
                //std::cout << "proximo " << *next << '\n';
                int ret = teg_fn(next, data);
                //std::cout << "return " << ret << '\n';
                // exec da funcao pegar no return next =
                r->push(ret);
            }
        }
    }
}  // namespace scheduler
