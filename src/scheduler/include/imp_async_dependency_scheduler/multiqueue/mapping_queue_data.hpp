#include <map>
#include <queue>
#include <vector>
namespace imp_async_dependency_scheduler {

    constexpr int empty = -1;
    constexpr int terminated = -2;
    constexpr int unavailable = -1;


    class MappingQueueData {
    public:
        MappingQueueData(int number_queue, int total) : mapping_queue_data(number_queue, empty), latest(-1), total(total) {
            for (int i = 0; i < number_queue; i++) {
                available_queue.push(i);
            }
        }

        void finish_data(int data) {
            int queue = mapping_data_queue[data];
            if (queue != -1 && queue != -2){
                mapping_queue_data[queue] = empty;
                available_queue.push(queue);
                mapping_data_queue[data] = terminated;
            }
        }

        int add_new_data(int data) {
            int queue = empty;
            if (!available_queue.empty()) {
                queue = available_queue.front();
                if (queue != empty) {
                    available_queue.pop();

                    mapping_data_queue[data] = queue;
                    mapping_queue_data[queue] = data;
                    latest = latest > data ? latest : data;
                }
            }

            return queue;
        }

        bool is_queue_available() { return !available_queue.empty(); }

        int queue_for_data(int data) {
            int queue = -1;

            auto it = mapping_data_queue.find(data);

            // adicionei isto do != terminated porque ele encontra o terminated aqui mas agora esta a empancar :/
            if (it != mapping_data_queue.end()) {
                // element found;
                queue = it->second;
            }

            return queue;
        }

        int check_if_new_data_index(int data) {
            int next_data = data;
            int current_data = mapping_data_queue[data];

            if (current_data == terminated) {
                latest = latest+1  < total && is_queue_available() ? latest + 1 : -1;
                next_data = latest;
            }

            return next_data;
        }

    private:
        // tamanho == numero de queues, o index da queue date o index do data
        std::vector<int> mapping_queue_data;
        std::map<int, int> mapping_data_queue;
        std::queue<int> available_queue;
        int latest;
        int total;
    };
}
