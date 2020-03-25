#include <thread>
#include <atomic>

#include "scheduler/master.hpp"
#include "scheduler/queue.hpp"
#include "scheduler/slave.hpp"

namespace scheduler {
#define SLAVE_SIZE 5

    void scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {

        std::shared_ptr<Queue<int>> q = std::make_shared<Queue<int>>();
        std::shared_ptr<Queue<int>> r = std::make_shared<Queue<int>>();
        std::vector<std::thread> slaves;

        for (uint thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&scheduler::slave, q, r, data_vec);
        }

        std::thread m(&scheduler::master, q, r, data_vec);


        for (auto &s : slaves){
            s.join();
        }
        m.join();

    }
}  // namespace scheduler
