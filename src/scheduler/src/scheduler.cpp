#include <atomic>
#include <thread>

#include "async_dependency_scheduler/master.hpp"
#include "async_dependency_scheduler/multiqueue.hpp"
#include "async_dependency_scheduler/slave.hpp"
#include "dependency_scheduler/master.hpp"
#include "dependency_scheduler/slave.hpp"
#include "dependency_scheduler_improved/master.hpp"
#include "dependency_scheduler_improved/slave.hpp"
#include "scheduler/master.hpp"
#include "scheduler/queue.hpp"
#include "scheduler/slave.hpp"
#include "vector.hpp"

#define SLAVE_SIZE 10

namespace scheduler {
void normal_scheduler(const std::shared_ptr<DataVector>& data_vec, int n_threads) {
    std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
    std::shared_ptr<::scheduler::Queue<int>> r = std::make_shared<::scheduler::Queue<int>>();
    std::vector<std::thread> slaves;

    for (int thread = 0; thread < (n_threads); thread++) {
        slaves.emplace_back(&scheduler::slave, q, r, data_vec);
    }

    std::thread m(&scheduler::master, q, r, data_vec);

    for (auto& s : slaves) {
        s.join();
    }
    m.join();
}
}  // namespace scheduler

namespace dependency_scheduler {

void dependency_scheduler(const std::shared_ptr<DataVector>& data_vec, int n_threads) {
    std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
    std::shared_ptr<::scheduler::Queue<std::pair<int, int>>> r =
        std::make_shared<::scheduler::Queue<std::pair<int, int>>>();
    std::vector<std::thread> slaves;

    for (int thread = 0; thread < (n_threads - 1); thread++) {
        slaves.emplace_back(&slave, q, r, data_vec);
    }

    std::thread m(&master, q, r, data_vec);

    for (auto& s : slaves) {
        s.join();
    }
    m.join();
}
}  // namespace dependency_scheduler

namespace dependency_scheduler_improved {

void dependency_scheduler_imp(const std::shared_ptr<DataVector>& data_vec, int n_threads) {
    std::shared_ptr<::scheduler::Queue<int>> q = std::make_shared<::scheduler::Queue<int>>();
    std::shared_ptr<::scheduler::Queue<std::pair<int, int>>> r =
        std::make_shared<::scheduler::Queue<std::pair<int, int>>>();
    std::vector<std::thread> slaves;

    for (int thread = 0; thread < (n_threads - 1); thread++) {
        slaves.emplace_back(&slave, q, r, data_vec);
    }

    std::thread m(&master, q, r, data_vec);

    for (auto& s : slaves) {
        s.join();
    }
    m.join();
}
}  // namespace dependency_scheduler_improved
namespace async_dependency_scheduler {
void dependency_scheduler_async(const std::shared_ptr<DataVector>& data_vec, int n_threads) {
    std::shared_ptr<Multiqueue> q = std::make_shared<Multiqueue>(2, data_vec->size());
    std::vector<std::thread> slaves;

    for (int thread = 0; thread < n_threads - 1; thread++) {
        slaves.emplace_back(&slave, q, data_vec);
    }

    std::thread m(&master, q);
    // master(q,data_vec);

    for (auto& s : slaves) {
        s.join();
    }
    m.join();
}
}  // namespace async_dependency_scheduler
