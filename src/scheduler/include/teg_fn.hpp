//
// Created by resende on 3/19/20.
//

#ifndef CLANG_BLUEPRINT_TEG_FN_HPP
#define CLANG_BLUEPRINT_TEG_FN_HPP

#include "data.hpp"
#include "pipeline.hpp"
#include "teg.h"

int teg_fn(int f, std::shared_ptr<Data> data);

int teg_fn(int f, Data *data) ;
#endif //CLANG_BLUEPRINT_TEG_FN_HPP
