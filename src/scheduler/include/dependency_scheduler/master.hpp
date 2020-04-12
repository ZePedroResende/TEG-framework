//
// Created by resende on 4/2/20.
//

#ifndef DEPENDENCY_SCHEDULER_MASTER_HPP
#define DEPENDENCY_SCHEDULER_MASTER_HPP

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

    void update_cache(std::map<int, int> *cache, std::pair<int, int> *pair) {
        auto it = cache->find(pair->first);
        if (it != cache->end()) it->second = pair->second;
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


    void master(const std::shared_ptr<scheduler::Queue<int>> &q,
                const std::shared_ptr<scheduler::Queue<std::pair<int, int>>> &r,
                const std::shared_ptr<std::vector<std::shared_ptr<Data>>> &data_vec) {
        auto cache = build_result_cache();
        static int initializer = 2;

        int current = 2;

        auto next_ints = get_no_deps_fns(initializer);
        for(auto & next: next_ints){
            q->push(& next);
        }

        while (!data_vec->empty()) {
            std::pair<int, int> *pair = r->next();
            int next = pair->second;
            // E necessario adicionar os que ja estao a ser processados
            if (current != pair->first) {
                update_cache(&cache, pair);
            } else {
                next = get_cache(&cache, pair->second);
            }

            if (next == TEG::FAIL) {
                data_vec->erase(data_vec->begin());

                next = 2;
            }

            if (next == TEG::SUCCESS) {
                std::cout << "TRUE\n";
                data_vec->erase(data_vec->begin());
                // save data
                next = 2;
            }

            if (!data_vec->empty()) {
                for(auto & n: get_no_deps_fns(next)){
                    q->push(& n);
                }
            }

        }
        q->stop();
    }
}  // namespace dependency_scheduler

#endif  // CLANG_BLUEPRINT_MASTER_HPP
