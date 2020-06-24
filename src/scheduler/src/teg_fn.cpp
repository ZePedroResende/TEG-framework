//
// Created by resende on 4/10/20.
//

#include <memory>

#include "data.hpp"
#include "pipeline.hpp"
#include "teg.h"

int teg_fn(int f, std::shared_ptr<Data> data) {
    int res = 1;
    switch (f) {
        case TEG::Prop1:
            res = Prop1(data.get());
            break;
        case TEG::Prop2:
            res = Prop2(data.get());
            break;
        case TEG::Prop3:
            res = Prop3(data.get());
            break;
        case TEG::Prop4:
            res = Prop4(data.get());
            break;
        default:
            break;
    }
    return res;
}

int teg_fn(int f, Data *data) {
    int res = 1;
    switch (f) {
        case TEG::Prop1:
            res = Prop1(data);
            break;
        case TEG::Prop2:
            res = Prop2(data);
            break;
        case TEG::Prop3:
            res = Prop3(data);
            break;
        case TEG::Prop4:
            res = Prop4(data);
            break;
        default:
            break;
    }
    return res;
}
