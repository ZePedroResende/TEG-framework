#include "scheduler/queue.hpp"
#include <data.hpp>

namespace scheduler {
void slave(const std::shared_ptr<scheduler::Queue<int>>& q,
          const std::shared_ptr<scheduler::Queue<int>>& r, const std::shared_ptr<std::vector<Data>>& data_vec) {

    while (!data_vec.get()->empty()){
      std::vector<Data> *data = data_vec.get();


      int *next = r->next();
        // exec da funcao pegar no return next =




      q->push(next);
  }
}
}  // namespace scheduler
