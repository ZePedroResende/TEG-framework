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
        void push(T *elem) {
            std::unique_lock<std::mutex> lck(mutex);
            if (elem != nullptr) {
                queue.push(elem);
                cv.notify_one();
            }
        }

        T *next() {
            T *elem {0};
            std::unique_lock<std::mutex> lck(mutex);
            cv.wait(lck, [this] { return !queue.empty() || !this->running.load(); });

            if (!queue.empty()) {
				elem = queue.front();
				if (elem != nullptr) {
					queue.pop();
				}
            }

            return elem;
        }


        void stop() {
            std::unique_lock<std::mutex> lck(mutex);
            this->running.store(false);
            cv.notify_all();
        }

        Queue() : running(true) {}


    private:
        std::queue<T *> queue;
        std::mutex mutex;
        std::condition_variable cv;
        std::atomic<bool> running;

    };
}  // namespace scheduler

#endif
