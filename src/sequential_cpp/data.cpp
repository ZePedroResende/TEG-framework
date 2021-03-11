//
// Created by resende on 3/11/20.
#include <algorithm>
#include "data.hpp"
#include <random>
#include <vector>

template<typename T>
T get_random() {
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(-10, 10);
    return dis(e);
}

template<typename T>
void fill_matrix(std::vector<std::vector<T>> &t_matrix, int MATRIX_SIZE) {
    t_matrix = std::vector<std::vector<T>>(MATRIX_SIZE, std::vector<T>(MATRIX_SIZE));

    for (std::vector<T> &line : t_matrix) {
        std::generate(line.begin(), line.end(), get_random<T>);
    }
}

template<typename T>
void fill_list(std::vector<T> &t_list, int LIST_SIZE) {
    t_list.resize(LIST_SIZE);
    std::generate(t_list.begin(), t_list.end(), get_random<T>);
}

template<typename T>
void fill_vector(std::vector<T> &t_vector, int VEC_SIZE) {
    t_vector.resize(VEC_SIZE);
    std::generate(t_vector.begin(), t_vector.end(), get_random<T>);
}



Data::Data(int VEC_SIZE, int MATRIX_SIZE, int LIST_SIZE){

     this->VEC_SIZE = VEC_SIZE;
     this->MATRIX_SIZE = MATRIX_SIZE;
     this->LIST_SIZE = LIST_SIZE;


    fill_vector(this->m_vector_float_a,this->VEC_SIZE);
    fill_vector(this->m_vector_float_b,this->VEC_SIZE);
    fill_vector(this->m_vector_float_c,this->VEC_SIZE);

    fill_vector(this->m_vector_int_a, this->VEC_SIZE);
    fill_vector(this->m_vector_int_b, this->VEC_SIZE);
    fill_vector(this->m_vector_int_c, this->VEC_SIZE);

    fill_matrix(this->m_matrix_a, this->MATRIX_SIZE);
    fill_matrix(this->m_matrix_b, this->MATRIX_SIZE);
    fill_matrix(this->m_matrix_c, this->MATRIX_SIZE);

    fill_matrix(this->m_matrix_float_a, this->MATRIX_SIZE);
    fill_matrix(this->m_matrix_float_b, this->MATRIX_SIZE);
    fill_matrix(this->m_matrix_float_c, this->MATRIX_SIZE);

    fill_list(this->m_list_ints, this->LIST_SIZE);
    fill_list(this->m_list_floats, this->LIST_SIZE);

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


int teg_fn(int f, Data *data) {
    int res = 1;
    switch (f) {
        case TEG::Prop1:
            res = data->Prop1();
            break;
        case TEG::Prop2:
            res = data->Prop2();
            break;
        case TEG::Prop3:
            res = data->Prop3();
            break;
        case TEG::Prop4:
            res = data->Prop4();
            break;
        default:
            break;
    }
    return res;
}
