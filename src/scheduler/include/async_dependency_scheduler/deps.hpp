    std::vector<int> get_no_deps_fns(int fn) {
        auto set = std::set<int>();
        set.insert(fn);
        if (dependency_map[static_cast<TEG::TEG>(fn)] == false) {
            auto functions = flow_map[static_cast<TEG::TEG>(fn)];
            for (const auto& function : functions) {
                if (dependency_map[static_cast<TEG::TEG>(function)] == false) {
                    auto vec = get_no_deps_fns(function);
                    set.insert(vec.begin(), vec.end());
                }
            }
        }
        std::vector<int> target(set.begin(), set.end());
        return target;
    }
