//
// Created by resende on 3/11/20.
#include <algorithm>
#include <data.hpp>
#include <random>
#include <vector>

template <typename T>
void fill_matrix(std::vector<std::vector<T>>& t_matrix) {
    t_matrix = std::vector<std::vector<T>>(MATRIX_SIZE, std::vector<T>(MATRIX_SIZE));

    for (std::vector<T>& line : t_matrix) {
        std::generate(line.begin(), line.end(), std::rand);
    }
}

template <typename T>
void fill_list(std::vector<T>& t_list) {
    t_list.resize(LIST_SIZE);
    std::generate(t_list.begin(), t_list.end(), std::rand);
}

template <typename T>
void fill_vector(std::vector<T>& t_vector) {
    t_vector.resize(VEC_SIZE);
    std::generate(t_vector.begin(), t_vector.end(), std::rand);
}

Data::Data() {
    fill_vector(this->m_vector_float_a);
    fill_vector(this->m_vector_float_b);
    fill_vector(this->m_vector_float_c);

    fill_vector(this->m_vector_int_a);
    fill_vector(this->m_vector_int_b);
    fill_vector(this->m_vector_int_c);

    fill_matrix(this->m_matrix_a);
    fill_matrix(this->m_matrix_b);
    fill_matrix(this->m_matrix_c);

    fill_matrix(this->m_matrix_float_a);
    fill_matrix(this->m_matrix_float_b);
    fill_matrix(this->m_matrix_float_c);

    fill_list(this->m_list_ints);
    fill_list(this->m_list_floats);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(1000.0, 100000.0);

    this->m_int_a = 1;
    this->m_int_b = 2;
    this->m_int_c = 3;

    this->m_float_a = 1.0;
    this->m_float_b = 2.0;
    this->m_float_c = 3.0;
    this->m_float_a = dist(mt);
    this->m_float_b = dist(mt);
    this->m_float_c = dist(mt);

    this->m_int_a = std::round(dist(mt));
    this->m_int_b = std::round(dist(mt));
    this->m_int_c = std::round(dist(mt));
}
