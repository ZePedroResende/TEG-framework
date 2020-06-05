#include <atomic>
#include <thread>

#include "dependency_scheduler/master.hpp"
#include "dependency_scheduler/slave.hpp"
#include "dependency_scheduler_improved/master.hpp"
#include "dependency_scheduler_improved/slave.hpp"
#include "scheduler/master.hpp"
#include "scheduler/queue.hpp"
#include "scheduler/slave.hpp"
#include "async_dependency_scheduler/master.hpp"
#include "async_dependency_scheduler/multiqueue.hpp"
#include "async_dependency_scheduler/slave.hpp"


#define SLAVE_SIZE 10

namespace scheduler {
    void normal_scheduler(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {
        std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
        std::shared_ptr<::scheduler::Queue<int>> r = std::make_shared<::scheduler::Queue<int>>();
        std::vector<std::thread> slaves;

        for (int thread = 0; thread < SLAVE_SIZE; thread++) {
            slaves.emplace_back(&scheduler::slave, q, r, data_vec);
        }

        std::thread m(&scheduler::master, q, r, data_vec);

        for (auto &s : slaves) {
            s.join();
        }
        m.join();
    }
}  // namespace scheduler

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
}  // namespace dependency_scheduler

namespace dependency_scheduler_improved {

    void dependency_scheduler_imp(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {
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


    namespace async_dependency_scheduler {
        void dependency_scheduler_async(const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {

            std::shared_ptr<Multiqueue<int>> q = std::make_shared<Multiqueue<int>>(2);
            std::shared_ptr<Multiqueue<std::pair<int, int>>> r =
                    std::make_shared<Multiqueue<std::pair<int, int>>>(2);
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
}  // namespace dependency_scheduler_improved
