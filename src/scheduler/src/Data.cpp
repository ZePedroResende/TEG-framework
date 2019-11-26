//
// Created by resende on 11/25/19.
//

#include "Data.hpp"
#include <random>

Data::Data() {
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
}
