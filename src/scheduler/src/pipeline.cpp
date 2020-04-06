//
// Created by resende on 3/18/20.
#include "teg.h"

int Prop1(int thread_id, Data* data) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    if (a == 1 && b > 1) {
        return TEG::Prop2;
    }

    if (b + 1 > 0) {
        if (((c + 1) != 0) && d == 1) return TEG::Prop3;

        return TEG::Prop4;
    }
    return TEG::FAIL;
}

int Prop2(int thread_id, Data* data) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    if (a == 0 && b + 1 > 0) {
        if (!c && d)
            return TEG::Prop3;

        else
            return TEG::Prop4;
    }

    return TEG::FAIL;
}

int Prop3(int thread_id, Data* data) {
    int a = 0;
    if (a > 0) {
        return TEG::SUCCESS;
    }
    return TEG::FAIL;
}

int Prop4(int thread_id, Data* data) {
    int a = 1;
    if (a > 0) {
        return TEG::SUCCESS;
    }
    return TEG::FAIL;
}

//
