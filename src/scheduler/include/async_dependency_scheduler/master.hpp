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
    MasterState(const std::shared_ptr<Multiqueue>& queue)
        : master_state(queue->get_size()), cache(queue->get_size()), queue(queue) {}

    void initialize() {
        // int division = deps.size() / number_threads_pool;
        // int queues_to_be_used = division > NUMBER_QUEUE ? NUMBER_QUEUE : division;

        for (int i = 0; i < master_state.size(); i++) {
            auto deps = get_no_deps_fns(master_state[i].current);

            for (auto& n : deps) {
                int function = n;
                queue->process(i, function);
            }
        }
    }

    void loop() {
        while (!queue->is_terminated()) {
            DataOutput output = queue->get_ouput();
            if (output.data != -1) {
                cache.update(output);

                auto state = master_state[output.data];
                if (cache.is_processed(output.data)) {
                    int next = cache.get_next(output.data, state.current);

                    state.next = next;
                    state.current = next;

                    if (next == TEG::FAIL) {
                         std::cout << "False" <<" "<< output.data << "\n";
                        queue->finish(output.data);
                        cache.reset(output.data);

                        state.next = 2;
                        state.current = 2;
                    }

                    if (next == TEG::SUCCESS) {
                        std::cout << "True" <<" "<< output.data << "\n";
                        // std::cout << "TRUE\n";
                        queue->finish(output.data);
                        cache.reset(output.data);

                        state.next = 2;
                        state.current = 2;
                    }

                    if (!queue->is_terminated()) {
                        int data_index = queue->get_data_index(output.data);

                        if (data_index != -1){
                            for (auto& n : get_no_deps_fns(next)) {
                                if (n != -2) {
                                    int function = n;
                                    queue->process(data_index, function);
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
    const std::shared_ptr<Multiqueue>& queue;
};

void master(const std::shared_ptr<Multiqueue>& queue,
            const std::shared_ptr<std::vector<std::shared_ptr<Data>>>& data_vec) {
    auto master_state = MasterState(queue);

    master_state.initialize();
    master_state.loop();
}

};  // namespace async_dependency_scheduler
