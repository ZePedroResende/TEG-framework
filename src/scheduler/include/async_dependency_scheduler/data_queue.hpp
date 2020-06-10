#pragma once
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

#include "mapping_queue_data.hpp"

class DataQueue {
   public:
    DataQueue(int total)
        : mapping_queue_data(total), insertion_order(total), total(total), finished(0) {}

    void finish_data(int data) {
        mapping_queue_data.finish_data(data);
        insertion_order.erase(std::remove(insertion_order.begin(), insertion_order.end(), data),
                              insertion_order.end());
        finished++;
    }

    int add_new_data(int data) {
        int added = -1;
        if (!mapping_queue_data.is_queue_available()) {
            added = mapping_queue_data.add_new_data(data);
            if (added) {
                insertion_order.push_back(data);
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

    std::vector<int> get_insertion_order() { return insertion_order; }

    int check_if_new_data_index(int data_index) {
        return mapping_queue_data.check_if_new_data_index(data_index);
    }

   private:
    // ordem em que o bloco de dados foi iniciado , index 1 depoi 2 depois 3
    // isto para ter uma especie  de priority queue

    MappingQueueData mapping_queue_data;
    std::vector<int> insertion_order;
    int total;
    int finished;
};
