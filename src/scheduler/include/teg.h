//
// Created by resende on 3/18/20.
//

#ifndef CLANG_BLUEPRINT_TEG_H
#define CLANG_BLUEPRINT_TEG_H

#include "data.hpp"
#include "map"

typedef int (*FnPtr)(int, Data);

namespace TEG {
    enum TEG { SUCCESS, FAIL, Prop1, Prop2, Prop3, Prop4 };

}

#endif //CLANG_BLUEPRINT_TEG_H
