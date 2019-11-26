//
// Created by resende on 11/25/19.
//

#ifndef SCHEDULER_MASTER_DATA_HPP
#define SCHEDULER_MASTER_DATA_HPP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

static const int VEC_SIZE = 1000;
static const int MATRIX_SIZE = 1000;
static const int LIST_SIZE = 10000;

class Data {
public:
  Data();

private:
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

  template <typename T> void fill_vector(std::vector<T> &t_vector) {
    t_vector.resize(VEC_SIZE);
    std::generate(t_vector.begin(), t_vector.end(), std::rand);
  }

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
};

#endif // SCHEDULER_MASTER_DATA_HPP
