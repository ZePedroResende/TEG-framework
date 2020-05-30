#ifndef MULTIQUEUE_H
#define MULTIQUEUE_H
#include <vector>

#include "scheduler/queue.hpp"
template <class T>
class Multiqueue {
   private:
    std::vector<scheduler::Queue<T>> multiqueue;

   public:
    Multiqueue(int size) : multiqueue(size) {}
    virtual ~Multiqueue();

    void add_to_queue(int queue, T value) { multiqueue[queue].push(value); }

    T get_from_queue(int queue) { multiqueue[queue].next(); }
};

#endif /* MULTIQUEUE_H */
