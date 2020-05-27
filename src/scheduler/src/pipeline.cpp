//
// Created by resende on 3/18/20.
#include "teg.h"
#include <cstdlib>
#include <ctime>
#include <logger.hpp>

int Prop1(int thread_id, Data *data) {
    int a = data->m_int_a;
    int b = data->m_int_b;
    int c = data->m_int_c;
    int d = data->m_list_ints[0];

    if (a == 1 && b > 1) {
        return TEG::Prop4;
    }

    if (b + 1 > 0) {
        if (((c + 1) != 0) && d == 1) return TEG::Prop3;

        return TEG::Prop2;
    }
    return TEG::FAIL;
}

int Prop2(int thread_id, Data *data) {
    int a = data->m_vector_int_a[2];
    int b = data->m_vector_int_b[4];
    int c = data->m_vector_int_b[3];
    int d = data->m_list_ints[1];
    srand((unsigned) time(0));
    int random = (rand() % 2);
    //logger::instance().log("Random " + std::to_string(random));

    if (1) {
        if (1) {

            //logger::instance().log("prop3");
            return TEG::Prop3;
        } else {

            //logger::instance().log("prop4");
            return TEG::Prop4;
        }
    }

    return TEG::FAIL;
}

int Prop3(int thread_id, Data *data) {
    auto d1 = data->m_matrix_a;
    auto d2 = data->m_matrix_b;
    auto d3 = data->m_matrix_c;

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    data->m_matrix_a = d3;

    //logger::instance().log("Running the prop3");
    return TEG::Prop4;
}

int Prop4(int thread_id, Data *data) {
    int a = 1;


    auto d1 = data->m_matrix_float_a;
    auto d2 = data->m_matrix_float_c;
    auto d3 = data->m_matrix_float_b;

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d2, d1);
    dot_prod_matrix(d3, d1, d2);

    data->m_matrix_float_b = d3;
    if (a > 0) {
        return TEG::SUCCESS;
    }
    return TEG::FAIL;
}

//
