#ifndef SCHEDULER_QUEUE_HPP
#define SCHEDULER_QUEUE_HPP
#include <condition_variable>
#include <mutex>
#include <queue>

namespace scheduler {
template <class T>
class Queue {
   public:
    void push(T* elem) {
        std::unique_lock<std::mutex> lck(mutex);
        if (elem != nullptr) {
            queue.push(elem);
            cv.notify_one();
        }
    }

    T* next() {
        T* elem = nullptr;

        std::unique_lock<std::mutex> lck(mutex);
        cv.wait(lck, [this] { return !queue.empty(); });

        if (!queue.empty()) {
            elem = queue.front();
            queue.pop();
        }

        return elem;
    }

   private:
    std::queue<T*> queue;
    std::mutex mutex;
    std::condition_variable cv;
};

}  // namespace scheduler

#endif
