#ifndef SCHEDULER_QUEUE_HPP
#define SCHEDULER_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <atomic>

namespace scheduler {
    template<class T>
    class Queue {
    public:
        void push(T elem) {
            std::unique_lock<std::mutex> lck(mutex);
            queue.push(elem);
            cv.notify_one();
        }

        T next() {
            T elem = T();
            std::unique_lock<std::mutex> lck(mutex);
            cv.wait(lck, [this] { return !queue.empty() || !this->running.load(); });

            if (!queue.empty()) {
                elem = queue.front();
                queue.pop();
            }

            return elem;
        }


        void stop() {
            std::unique_lock<std::mutex> lck(mutex);
            this->running.store(false);
            cv.notify_all();
        }

        void print_queue() {
            std::unique_lock<std::mutex> lck(mutex);
            cv.wait(lck, [this] { return !queue.empty() || !this->running.load(); });
            std::queue<T *> q(queue);
            while (!q.empty()) {
                int a = *q.front();
                std::cout << " " << a;
                q.pop();
            }
            std::cout << std::endl;
        }


        Queue() : running(true) {}


    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<bool> running;

    };
}  // namespace scheduler

#endif
