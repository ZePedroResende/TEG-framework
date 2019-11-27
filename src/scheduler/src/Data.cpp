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
const std::vector<float> &Data::getMVectorFloatA() const {
  return m_vector_float_a;
}
void Data::setMVectorFloatA(const std::vector<float> &mVectorFloatA) {
  m_vector_float_a = mVectorFloatA;
}
const std::vector<float> &Data::getMVectorFloatB() const {
  return m_vector_float_b;
}
void Data::setMVectorFloatB(const std::vector<float> &mVectorFloatB) {
  m_vector_float_b = mVectorFloatB;
}
const std::vector<float> &Data::getMVectorFloatC() const {
  return m_vector_float_c;
}
void Data::setMVectorFloatC(const std::vector<float> &mVectorFloatC) {
  m_vector_float_c = mVectorFloatC;
}
const std::vector<int> &Data::getMVectorIntA() const { return m_vector_int_a; }
void Data::setMVectorIntA(const std::vector<int> &mVectorIntA) {
  m_vector_int_a = mVectorIntA;
}
const std::vector<int> &Data::getMVectorIntB() const { return m_vector_int_b; }
void Data::setMVectorIntB(const std::vector<int> &mVectorIntB) {
  m_vector_int_b = mVectorIntB;
}
const std::vector<int> &Data::getMVectorIntC() const { return m_vector_int_c; }
void Data::setMVectorIntC(const std::vector<int> &mVectorIntC) {
  m_vector_int_c = mVectorIntC;
}
const std::vector<std::vector<int>> &Data::getMMatrixA() const {
  return m_matrix_a;
}
void Data::setMMatrixA(const std::vector<std::vector<int>> &mMatrixA) {
  m_matrix_a = mMatrixA;
}
const std::vector<std::vector<int>> &Data::getMMatrixB() const {
  return m_matrix_b;
}
void Data::setMMatrixB(const std::vector<std::vector<int>> &mMatrixB) {
  m_matrix_b = mMatrixB;
}
const std::vector<std::vector<int>> &Data::getMMatrixC() const {
  return m_matrix_c;
}
void Data::setMMatrixC(const std::vector<std::vector<int>> &mMatrixC) {
  m_matrix_c = mMatrixC;
}
const std::vector<std::vector<float>> &Data::getMMatrixFloatA() const {
  return m_matrix_float_a;
}
void Data::setMMatrixFloatA(
    const std::vector<std::vector<float>> &mMatrixFloatA) {
  m_matrix_float_a = mMatrixFloatA;
}
const std::vector<std::vector<float>> &Data::getMMatrixFloatB() const {
  return m_matrix_float_b;
}
void Data::setMMatrixFloatB(
    const std::vector<std::vector<float>> &mMatrixFloatB) {
  m_matrix_float_b = mMatrixFloatB;
}
const std::vector<std::vector<float>> &Data::getMMatrixFloatC() const {
  return m_matrix_float_c;
}
void Data::setMMatrixFloatC(
    const std::vector<std::vector<float>> &mMatrixFloatC) {
  m_matrix_float_c = mMatrixFloatC;
}
int Data::getMIntA() const { return m_int_a; }
void Data::setMIntA(int mIntA) { m_int_a = mIntA; }
int Data::getMIntB() const { return m_int_b; }
void Data::setMIntB(int mIntB) { m_int_b = mIntB; }
int Data::getMIntC() const { return m_int_c; }
void Data::setMIntC(int mIntC) { m_int_c = mIntC; }
float Data::getMFloatA() const { return m_float_a; }
void Data::setMFloatA(float mFloatA) { m_float_a = mFloatA; }
float Data::getMFloatB() const { return m_float_b; }
void Data::setMFloatB(float mFloatB) { m_float_b = mFloatB; }
float Data::getMFloatC() const { return m_float_c; }
void Data::setMFloatC(float mFloatC) { m_float_c = mFloatC; }
const std::vector<int> &Data::getMListInts() const { return m_list_ints; }
void Data::setMListInts(const std::vector<int> &mListInts) {
  m_list_ints = mListInts;
}
const std::vector<float> &Data::getMListFloats() const { return m_list_floats; }
void Data::setMListFloats(const std::vector<float> &mListFloats) {
  m_list_floats = mListFloats;
}
