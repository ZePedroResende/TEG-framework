//
// Created by resende on 4/2/20.
//

#ifndef TEG_DEPENDENCY_HPP
#define TEG_DEPENDENCY_HPP

#include <vector>
#include <string>
#include <map>
#include "teg.h"

std::map<TEG::TEG, std::vector<TEG::TEG>> dependency_map = {
        {TEG::Prop1, {TEG::Prop3, TEG::Prop4}},
        {TEG::Prop2, {TEG::Prop3, TEG::Prop4}},
        {TEG::Prop3, {}},
        {TEG::Prop4, {}}
};

static const std::vector<TEG::TEG> *dependency(TEG::TEG fn) {
    auto it = dependency_map.find(fn);

    if (it == dependency_map.end()){
        return nullptr;
    }

    return &it->second;
}

#endif //CLANG_BLUEPRINT_TEG_DEPENDENCY_HPP
