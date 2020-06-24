//
// Created by resende on 4/26/20.
//

#ifndef TEG_UTIL_HPP
#define TEG_UTIL_HPP

#include <atomic>
#include <data.hpp>
#include <utility>
#include <set>

#include "scheduler/queue.hpp"
#include "teg.h"
#include "teg_dependency.hpp"

namespace dependency_scheduler {

    std::map<int, int> build_result_cache() {
        std::map<int, int> map;

        for (auto const &key : flow_map) {
            map.insert(std::make_pair(key.first, -1));
        }
        return map;
    }

    void update_cache(std::map<int, int> *cache, std::pair<int, int> pair) {
        auto it = cache->find(pair.first);
        if (it != cache->end()) it->second = pair.second;
    }

    int get_cache(std::map<int, int> *cache, int next) {
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

    std::vector<int> get_no_deps_fns(int fn) {
        auto set = std::set<int>();
        set.insert(fn);
        if (dependency_map[static_cast<TEG::TEG>(fn)] == false) {
            auto functions = flow_map[static_cast<TEG::TEG>(fn)];
            for (const auto &function : functions) {
                if (dependency_map[static_cast<TEG::TEG>(function)] == false) {
                    auto vec = get_no_deps_fns(function);
                    set.insert(vec.begin(), vec.end());
                }
            }
        }
        std::vector<int> target(set.begin(), set.end());
        return target;
    }

    bool is_processed(std::map<int, int> *map) {
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

    int get_next(int current, std::map<int, int> *map) {


        int next = (*map)[current];
        while( next != 1 && next != 0){
            int current = next;
            next = (*map)[current];
            if (next == -1 ){
                return current;
            }
        }

        return next;
    }
}
#endif //TEG_UTIL_HPP
