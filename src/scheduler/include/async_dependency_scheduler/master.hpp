#pragma once

#include "multiqueue.hpp"
#include "cache.hpp"
#include "deps.hpp"

namespace async_dependency_scheduler {

struct IndexState {
    int current ;
    int next ;
    
    IndexState() :  current(2), next(-1) { 
    }
};

class MasterState {
   public:
    MasterState( const std::shared_ptr<Multiqueue>& queue): master_state(queue->get_size()), cache(queue->get_size()), queue(queue) {}

    void initialize() {


        //int division = deps.size() / number_threads_pool;
        //int queues_to_be_used = division > NUMBER_QUEUE ? NUMBER_QUEUE : division;


        for (int i = 0; i <  master_state.size; i++) {

			auto deps = get_no_deps_fns(master_state[i].current);


            for (auto &n : deps) {
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

                 if (cache.is_processed(output.data)) {
					 auto state= master_state[output.data];
					 int next = cache.get_next(output.data, state.current );

                     state.current = next;

                     // Fazer agora os ifs das cenas diferentes 
                 }
                 // fazer o else caso ainda exista cenas a processar dependentes
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

}  // namespace async_dependency_scheduler
