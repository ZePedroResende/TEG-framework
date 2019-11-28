//
// Created by resende on 11/28/19.
//

#ifndef SCHEDULER_MASTER_FILTERS_HPP
#define SCHEDULER_MASTER_FILTERS_HPP
#include <algorithm>
#include <random>
#include <vector>
#


template <typename T>
void prod_matrix(std::vector<std::vector<T>> &a, std::vector<std::vector<T>> &b,
                 std::vector<std::vector<T>> &c) {

  int height = b.size();
  int width = b[0].size();
  int width_b = c.size();

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width_b; j++) {
      a[i][j] = 0;
      for (int k = 0; k < width; k++) {
        a[i][j] += b[i][k] * c[k][j];
      }
    }
  }
}

template <typename T>
void dot_prod_matrix(std::vector<std::vector<T>> &a,
                     std::vector<std::vector<T>> &b,
                     std::vector<std::vector<T>> &c) {

  int height = a.size();
  int width = a[0].size();

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      a[i][j] = b[i][j] * c[i][j];
    }
  }
}

template <typename T> bool is_positive(T number) { return number > 0; }

template <typename T> void add(T &number) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 10000);
  number += distr(eng);
}

template <typename T> void filter_list(std::vector<T> &list, T number) {

  std::vector<T> ret;
  std::copy_if(list.begin(), list.end(), std::back_inserter(ret),
               [&number](T i) { return i >= number; });
  list = ret;
}

template <typename T> void random_vector(std::vector<T> &vector) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 10000);

  for (auto &item : vector)
    item = distr(eng);
}

template <typename T> void random_matrix(std::vector<std::vector<T>> &matrix) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 10000);

  for (auto &line : matrix)
    for (auto &item : line)
      item = distr(eng);
}

}

template <typename T> void random_number(T &number) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 10000);
  number = distr(eng);
}
#endif // SCHEDULER_MASTER_FILTERS_HPP
