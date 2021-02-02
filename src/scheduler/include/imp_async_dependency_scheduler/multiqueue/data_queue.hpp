#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <set>

#include "mapping_queue_data.hpp"


namespace imp_async_dependency_scheduler {
    class DataQueue {
    public:
        DataQueue(int queues, int total_data)
                : mapping_queue_data(queues, total_data), insertion_order(), total(total_data), finished(0) {}

        void finish_data(int data) {
            mapping_queue_data.finish_data(data);
            insertion_order.erase(data);
            finished++;
        }

        int add_new_data(int data) {
            int added = -1;
            if (mapping_queue_data.is_queue_available()) {
                added = mapping_queue_data.add_new_data(data);
                if (added != -1) {
                    insertion_order.insert(data);
                }
            }

            return added;
        }

        int get_data_queue(int data) {
            int queue = -1;
            queue = mapping_queue_data.queue_for_data(data);

            if (queue == -1) {
                queue = add_new_data(data);
            }

            return queue;
        }

        bool is_queue_available() { return !mapping_queue_data.is_queue_available(); }

        bool is_terminated() { return total == finished; }

        std::set<int> get_insertion_order() { return insertion_order; }

        int check_if_new_data_index(int data_index) {
            return mapping_queue_data.check_if_new_data_index(data_index);
        }

    private:
        // ordem em que o bloco de dados foi iniciado , index 1 depoi 2 depois 3
        // isto para ter uma especie  de priority queue

        MappingQueueData mapping_queue_data;
        std::set<int> insertion_order;
        int total;
        int finished;
    };
}
