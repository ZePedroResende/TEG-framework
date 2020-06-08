class Cache {
   public:
    Cache(int number_queue) : map(number_queue) { 
        for (int i = 0; i < number_queue; i++) {
            map.push_back(build_result_cache());
        }
    }


    void update(int queue_index, std::pair<int, int>* pair) {
        auto cache = map[queue_index];
        auto it = cache->find(pair->first);
        if (it != cache->end()) it->second = pair->second;
    }

    int get(int queue_index, int next) {
        int res = next;

        auto it = cache->find(next);

        if (it != cache->end()) {
            if (it->second != -1)
                res = get_cache(cache, it->second);
            else
                res = next;
        }
        return res;
    }


    bool is_processed(int queue_index) {
        int value = -2;
        bool bResult = true;
        auto it = map->begin();
        // Iterate through the map
        while (it != map->end()) {
            // Check if value of this entry matches with given value
            if (it->second == value) {
                // Yes found
                bResult = false;
                // Push the key in given map
                break;
            }
            // Go to next entry in map
            it++;
        }
        return bResult;
    }

    int get_next(int queue_index, int current) {
        int next = (*map)[current];
        while (next != 1 && next != 0) {
            int current = next;
            next = (*map)[current];

            if (next == -1 || next == -2) {
                return current;
            }
        }

        return next;
    }

    void reset(int queue_index) { map[queue_index] = build_result_cache()
    }




   private:
    std::vector<std::map<int, int>> map;


    std::map<int, int> build_result_cache() {
        std::map<int, int> map;

        for (auto const& key : flow_map) {
            map.insert(std::make_pair(key.first, -1));
        }
        return map;
    }
};
