//
// Created by resende on 3/11/20.
#include <algorithm>
#include <random>
#include <vector>
#include <data.hpp>

template <typename T>
void fill_matrix(std::vector<std::vector<T>> &t_matrix) {
    t_matrix =
        std::vector<std::vector<T>>(MATRIX_SIZE, std::vector<T>(MATRIX_SIZE));

    for (std::vector<T> &line : t_matrix) {
        std::generate(line.begin(), line.end(), std::rand);
    }
}

template <typename T> void fill_list(std::vector<T> &t_list) {
    t_list.resize(LIST_SIZE);
    std::generate(t_list.begin(), t_list.end(), std::rand);
}


template <typename T> void fill_vector(std::vector<T> &t_vector) {
    t_vector.resize(VEC_SIZE);
    std::generate(t_vector.begin(), t_vector.end(), std::rand);
}


Data init_data() {
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
    fill_vector(m_vector_float_a);
    fill_vector(m_vector_float_b);
    fill_vector(m_vector_float_c);

    fill_vector(m_vector_int_a);
    fill_vector(m_vector_int_b);
    fill_vector(m_vector_int_c);

    fill_matrix(m_matrix_a);
    fill_matrix(m_matrix_b);
    fill_matrix(m_matrix_c);

    fill_matrix(m_matrix_float_a);
    fill_matrix(m_matrix_float_b);
    fill_matrix(m_matrix_float_c);

    fill_list(m_list_ints);
    fill_list(m_list_floats);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(1000.0, 100000.0);

    m_float_a = dist(mt);
    m_float_b = dist(mt);
    m_float_c = dist(mt);

    m_int_a = std::round(dist(mt));
    m_int_b = std::round(dist(mt));
    m_int_c = std::round(dist(mt));

    Data d = Data{
        m_vector_float_a, m_vector_float_b, m_vector_float_c, m_vector_int_a, m_vector_int_b,
        m_vector_int_c,   m_matrix_a,       m_matrix_b,       m_matrix_c,     m_matrix_float_a,
        m_matrix_float_b, m_matrix_float_c, m_int_a,          m_int_b,        m_int_c,
        m_float_a,        m_float_b,        m_float_c,        m_list_ints,    m_list_floats,
    };

    return d;
}

