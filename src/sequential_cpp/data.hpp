//
// Created by resende on 03/03/20.
//

#ifndef DATA_HPP
#define DATA_HPP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "teg.h"



template <typename T>
void dot_prod_matrix(std::vector<std::vector<T>>& a, std::vector<std::vector<T>>& b,
                     std::vector<std::vector<T>>& c) {
    int height = a.size();
    int width = a[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            a[i][j] = b[i][j] * c[i][j];
        }
    }
}

class Data {
   public:
    Data() : Data(1000, 1000, 1000) {}
    Data(int MATRIX_SIZE) : Data(1000, MATRIX_SIZE, 1000) {}

    Data(int VEC_SIZE, int MATRIX_SIZE, int LIST_SIZE);

    std::vector<float> m_vector_float_a;
    std::vector<float> m_vector_float_b;
    std::vector<float> m_vector_float_c;
    std::vector<int> m_vector_int_a;
    std::vector<int> m_vector_int_b;
    std::vector<int> m_vector_int_c;
    std::vector<std::vector<int>> m_matrix_a;
    std::vector<std::vector<int>> m_matrix_b;
    std::vector<std::vector<int>> m_matrix_c;
    std::vector<std::vector<float>> m_matrix_float_a;
    std::vector<std::vector<float>> m_matrix_float_b;
    std::vector<std::vector<float>> m_matrix_float_c;
    int m_int_a{};
    int m_int_b{};
    int m_int_c{};
    float m_float_a;
    float m_float_b;
    float m_float_c;
    std::vector<int> m_list_ints;
    std::vector<float> m_list_floats;

    int VEC_SIZE;
    int MATRIX_SIZE;
    int LIST_SIZE;

int Prop1() {

    int a = this->m_int_a;
    int b = this->m_int_b;
    int c = this->m_int_c;
    int d = this->m_list_ints[0];
    if (a == 1 && b > 1) {
        return TEG::Prop2;
    }

    if (b + 1 > 0) {
        if (((c + 1) != 0) && d == 1) return TEG::Prop3;

        return TEG::Prop2;
    }
    return TEG::FAIL;

}

int Prop2() {
/*    int a = this->m_vector_int_a[2];
    int b = this->m_vector_int_b[4];
    int c = this->m_vector_int_b[3];
    int d = this->m_list_ints[1];
    srand((unsigned) time(0));
    int random = (rand() % 2);
    */
    //logger::instance().log("Random " + std::to_string(random));
    auto d1 = this->m_matrix_a;
    auto d2 = this->m_matrix_b;
    auto d3 = this->m_matrix_c;

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);
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

int Prop3( ) {
    auto d1 = this->m_matrix_a;
    auto d2 = this->m_matrix_b;
    auto d3 = this->m_matrix_c;

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    this->m_matrix_a = d3;

    //logger::instance().log("Running the prop3");
    return TEG::Prop4;
}

int Prop4() {
    int a = 1;


    auto d1 = this->m_matrix_float_a;
    auto d2 = this->m_matrix_float_c;
    auto d3 = this->m_matrix_float_b;

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d2, d1);
    dot_prod_matrix(d3, d1, d2);

    this->m_matrix_float_b = d3;
    if (a > 0) {
        return TEG::SUCCESS;
    }
    return TEG::FAIL;

}



};

int teg_fn(int f, Data *data) ;
#endif  // DATA_HPP
