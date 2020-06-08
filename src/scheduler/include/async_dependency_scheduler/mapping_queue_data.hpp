constexpr int empty = -1;
constexpr int unavailable = -1;

class MappingQueueData {
   public:
    MappingQueueData(int number_queue) : mapping_queue_data(number_queue, empty) {
        for (int i = 0; i < number_queue; i++) {
            available_queue.push(i);
        }
    }

    void finish_data(int data) { 
        int queue = mapping_data_queue[data];
        mapping_queue_data[queue] = -1;
        available_queue.push(data);
    }

    int add_new_data(int data) { 
        int queue = -1 ;
            if (!available_queue.empty()) {
                queue = available_queue.front();
                if (queue != -1 ) {
                    available_queue.pop();

					mapping_data_queue[data] = queue;
                    mapping_queue_data[queue] = data;
                }
            }

     return queue;
    }

    bool is_queue_available() { 
        return !available_queue.empty();
    }

    int queue_for_data(int data) {
		int queue = -1;

        auto it = mapping_data_queue.find(data);

		if(it != mapping_data_queue.end())
		{
		   //element found;
		   queue = it->second;
		}

		return queue;
    }


   private:

    // tamanho == numero de queues, o index da queue date o index do data
    std::vector<int> mapping_queue_data;
    std::map<int, int> mapping_data_queue;
    std::queue<int> available_queue;

};
