#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

#include "async_dependency_scheduler/multiqueue/data_queue.hpp"

// isto e so para input ? ou faz sentido meter o input e out na mesma class ?
// por um lado ja temos as queue era so duplicar o execution_queue_vector
// ou poderiamos ter um unico vetor com todos os outputs e identificados com a queue id ou assim
// Varias queue de output deve ser mais facil paralelizar

// se utilizarmos isto para input e output num so
// abstrair a multiqueue para efetivamente ser so uma multi queue e chamar isto outra cena
// tipo data_mapping ou assim
// fuck me xD

struct DataFunction {
    bool has_data;
    int data;
    int function;
};

struct Output {
    int function_id;
    int output;
};

struct DataOutput {
    int data;
    Output output;
};

class Multiqueue {
   public:
    Multiqueue(int size, int total_data)
        : data_queue(size, total_data),
          size(size),
          execution_queue_vector(size, std::queue<int>()),
          output_queue_vector(size, std::queue<Output>()) {}

    bool process(int data_index, const int function_id) {
        std::unique_lock<std::mutex> lck(mutex);

        int queue = data_queue.get_data_queue(data_index);

        if (queue != -1) {
            execution_queue_vector[queue].push(function_id);
        }

        return queue != -1;
    }

    DataFunction next_to_process() {
        std::unique_lock<std::mutex> lck(mutex);

        std::set<int> insertion_order = data_queue.get_insertion_order();

        auto it = insertion_order.begin();

        for (; it != insertion_order.end() &&
               is_queue_empty(execution_queue_vector, data_queue.get_data_queue(*it));
             it++)
            ;

        if (it != insertion_order.end()) {
            int index = data_queue.get_data_queue(*it);
            int function = execution_queue_vector[index].front();
            execution_queue_vector[index].pop();

            return DataFunction{true, *it, function

            };
        } else {
            return DataFunction{false, -1, -1};
        }
    }

    void set_output(int data_index, const int function, int out) {
        std::unique_lock<std::mutex> lck(mutex);

        int queue = data_queue.get_data_queue(data_index);

        if (queue != -1 && queue != terminated) {
            output_queue_vector[queue].push(Output{function, out});
        }
    }

    DataOutput get_ouput() {
        std::unique_lock<std::mutex> lck(mutex);

        std::set<int> insertion_order = data_queue.get_insertion_order();

        auto it = insertion_order.begin();

        while (it != insertion_order.end()) {
            if (!is_queue_empty(output_queue_vector, data_queue.get_data_queue(*it))) {
                break;
            }
            it++;
        }

        if (it != insertion_order.end()) {
            int index = data_queue.get_data_queue(*it);
            Output output = output_queue_vector[index].front();

            output_queue_vector[index].pop();

            return DataOutput{*it, output};
        } else {
            return DataOutput{-1, Output{-1, -1}};
        }
    }

    void finish(int data_index) {
        std::unique_lock<std::mutex> lck(mutex);

        data_queue.finish_data(data_index);
    }

    int get_data_index(int data_index) { return data_queue.check_if_new_data_index(data_index); }
    int get_data_queue(int data_index) { return data_queue.get_data_queue(data_index); }

    int get_size() { return size; }

    bool is_terminated() { return data_queue.is_terminated(); }

   private:
    // keeps the order of priority of queue
    DataQueue data_queue;
    int size;

    // queue com as funcoes para realizar de cada um dos vetores em separado
    std::vector<std::queue<int>> execution_queue_vector;
    std::vector<std::queue<Output>> output_queue_vector;

    std::mutex mutex;
    std::condition_variable cv;

    template <typename T>
    bool is_queue_not_empty(std::vector<std::queue<T>> queue, int index) {
        return !queue[index].empty();
    }

    template <typename T>
    bool is_queue_empty(std::vector<std::queue<T>> queue, int index) {
        return queue[index].empty();
    }
};
