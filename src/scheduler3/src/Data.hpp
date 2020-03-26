//
// Created by resende on 03/03/20.
//

#ifndef SCHEDULER_MASTER_DATA_HPP
#define SCHEDULER_MASTER_DATA_HPP

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

static const int VEC_SIZE = 10000;
static const int MATRIX_SIZE = 10000;
static const int LIST_SIZE = 100000;

typedef struct DATA {
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
} Data;

#endif  // SCHEDULER_MASTER_DATA_HPP
