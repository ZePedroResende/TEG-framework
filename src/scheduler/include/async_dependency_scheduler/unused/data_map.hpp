#ifndef ASYNC_DEPENDENCY_SCHEDULER_SLAVE_HPP
#define ASYNC_DEPENDENCY_SCHEDULER_SLAVE_HPP

#include <logger.hpp>
#include <utility>

#include "data.hpp"
#include "queue.hpp"
#include "scheduler/queue.hpp"
#include "teg_fn.hpp"

namespace async_dependency_scheduler {
    class DataMap {
    public:
        std::vector<int> vector;
        std::vector<int> finished;
        int latest;
        int started;
        int total;

        DataMap(int size, int total) : vector(size, -1), finished(), latest(-1), started(0), total(total) {}

        void add_data_queue(int level, int queue) {
            started++;
            latest = level;
            vector[level] = queue;
        }

        bool is_queue_used(int level) {
            return vector[level] != -1;
        }

        int get_first_available() {
            int size = 0;
            for (; size < vector.size() && vector[size] == -1; size++) {
            }
            if (size < vector.size()) {
                return size;
            } else {
                return 0;
            }
        }

        int use_next_available(int queue) {
            int size = 0;
            for (; size < vector.size() && vector[size] != -1; size++) {
            }
            if (size < vector.size()) {
                vector[size] = queue;
                return size;
            } else {
                return -1;
            }

        }

        int get_latest() {
            return latest;
        }

        void terminate_data(int level) {
            finished.push_back(level);
            vector[level] = -1;
        }

        bool is_finished() {
            return finished.size() == total;
        }


    };
}  // namespace async_dependency_scheduler
#endif
