#include <thread>
#include <atomic>

#include "scheduler/master.hpp"
#include "dependency_scheduler/master.hpp"
#include "dependency_scheduler/slave.hpp"
#include "scheduler/queue.hpp"
#include "scheduler/slave.hpp"

namespace scheduler {
const constexpr int SLAVE_SIZE  = 5;
    void scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {
        std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
        std::shared_ptr<::scheduler::Queue<int>> r = std::make_shared<::scheduler::Queue<int>>();
        std::vector<std::thread> slaves;

        for (int thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&slave, q, r, data_vec);
        }

        std::thread m(&::scheduler::master, q, r, data_vec);

        for (auto &s : slaves){
            s.join();
        }
        m.join();

    }

    void dependency_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {

        std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
        std::shared_ptr<::scheduler::Queue<std::pair<int,int>>> r = std::make_shared<::scheduler::Queue<std::pair<int,int>>>();
        std::vector<std::thread> slaves;

        for (int thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&dependency_scheduler::slave, q, r, data_vec);
        }

        std::thread m(&dependency_scheduler::master, q, r, data_vec);

        for (auto &s : slaves){
            s.join();
        }
        m.join();

    }

}  // namespace scheduler
