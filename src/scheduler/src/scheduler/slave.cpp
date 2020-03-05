#include "scheduler/queue.hpp"

namespace scheduler {
/*
void slave(const std::shared_ptr<scheduler::Queue<int>>& q,
          const std::shared_ptr<scheduler::Queue<int>>& r) {

  int* next = q->next();
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
*/
}  // namespace scheduler
