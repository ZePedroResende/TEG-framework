#include <thread>
#include <atomic>
#include "dependency_scheduler/master_try.hpp"
#include "dependency_scheduler/slave.hpp"

#include "scheduler/master.hpp"
#include "scheduler/queue.hpp"
#include "scheduler/slave.hpp"

#define SLAVE_SIZE 5


namespace scheduler {
    void normal_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {

        std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
        std::shared_ptr<::scheduler::Queue<int>> r = std::make_shared<::scheduler::Queue<int>>();
        std::vector<std::thread> slaves;

        for (uint thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&scheduler::slave, q, r, data_vec);
        }

        std::thread m(&scheduler::master, q, r, data_vec);


        for (auto &s : slaves) {
            s.join();
        }
        m.join();

    }
}


namespace dependency_scheduler {

    void dependency_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {

        std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
        std::shared_ptr<::scheduler::Queue<std::pair<int, int>>> r =
                std::make_shared<::scheduler::Queue<std::pair<int, int>>>();
        std::vector<std::thread> slaves;

        for (int thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&slave, q, r, data_vec);
        }

        std::thread m(&master, q, r, data_vec);

        for (auto &s : slaves) {
            s.join();
        }
        m.join();

    }
}
