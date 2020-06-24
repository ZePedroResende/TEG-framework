#pragma once

#include "cache.hpp"
#include "data.hpp"
#include "deps.hpp"
#include "logger.hpp"
#include "multiqueue.hpp"

namespace async_dependency_scheduler {

    struct IndexState {
        int current;
        int next;

        IndexState() : current(2), next(-1) {}
    };

    class MasterState {
    public:
        MasterState(const std::shared_ptr<Multiqueue> &queue)
                : master_state(queue->get_size()), cache(queue->get_size()), queue(queue) {}

        void initialize() {
            // int division = deps.size() / number_threads_pool;
            // int queues_to_be_used = division > NUMBER_QUEUE ? NUMBER_QUEUE : division;

            for (size_t i = 0; i < master_state.size(); i++) {
                auto deps = get_no_deps_fns(master_state[i].current);

                for (auto n : deps) {
                    auto f = new int(n);
                    queue->process(i, *f);
                }
            }
        }

        void loop() {
            while (!queue->is_terminated()) {
                DataOutput output = queue->get_ouput();
                if (output.data != -1) {
                    // isto nao esta a ir buscar o index da queue seu burro , isto esta a ir buscar o data index novo se necessario !!!!!!
                    int queue_index = queue->get_data_queue(output.data);
                    cache.update(output, queue_index);

                    auto state = master_state[queue_index];
                    if (cache.is_processed(queue_index)) {
                        int next = cache.get_next(queue_index, state.current);

                        state.next = next;
                        state.current = next;

                        if (next == TEG::FAIL) {
                            //    std::cout << "False" << " " << output.data << "\n";
                            queue->finish(output.data);
                            cache.reset(queue_index);

                            state.next = 2;
                            state.current = 2;
                        }

                        if (next == TEG::SUCCESS) {
                            //     std::cout << "True" << " " << output.data << "\n";
                            // std::cout << "TRUE\n";
                            queue->finish(output.data);
                            cache.reset(queue_index);

                            state.next = 2;
                            state.current = 2;
                        }

                        if (!queue->is_terminated()) {
                            int data_index = queue->get_data_index(output.data);

                            if (data_index != -1) {
                                for (int n : get_no_deps_fns(state.next)) {
                                    if (n != -2) {
                                        auto f = new int(n);
                                        queue->process(data_index, *f);
                                    }
                                }
                            }
                        }

                        // Fazer agora os ifs das cenas diferentes
                    } else {
                        if (state.current == output.output.function_id) {
                            int next = cache.get_next(output.data, state.current);

                            state.next = next;
                            state.current = next;
                        }
                    }
                }
            }
        }

    private:
        std::vector<IndexState> master_state;
        Cache cache;
        const std::shared_ptr<Multiqueue> &queue;
    };

    void master(const std::shared_ptr<Multiqueue> &queue) {
        auto master_state = MasterState(queue);

        master_state.initialize();
        master_state.loop();
    }

}  // namespace async_dependency_scheduler
