#ifndef MULTIQUEUE_H
#define MULTIQUEUE_H

#include <vector>

#include "scheduler/queue.hpp"

template<class T>
class Multiqueue {
private:
    std::vector<scheduler::Queue<T>> multiqueue;

public:
    Multiqueue(int size) : multiqueue(size) {}

    virtual ~Multiqueue();

    void add_to_queue(int queue, T value) { multiqueue[queue].push(value); }

    T get_from_queue(int queue) { multiqueue[queue].next(); }

    std::pair<int, T> get_first_queue() {
        auto response = nullptr;
        for (auto it = multiqueue.begin(); it != multiqueue.end(); ++it) {
            response = it->get();
            if (response != nullptr) {
                return std::make_pair(it - multiqueue.begin(), response);
            }
        }
        return std::make_pair(-1, response);
    }
};

#endif /* MULTIQUEUE_H */
