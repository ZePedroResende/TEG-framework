//
// Created by resende on 03/03/20.
//

#ifndef DATA_HPP
#define DATA_HPP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class Data {
   public:
    Data() : Data(100, 100, 100) {}

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
};

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

#endif  // DATA_HPP
