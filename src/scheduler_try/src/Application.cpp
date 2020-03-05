//
// Created by resende on 11/28/19.
//
#include "Application.hpp"
#include <functional>

int a(Data t_data) {

  t_data.dot_prod_matrix_float_to_a();
  t_data.prod_matrix_float_to_a();
  if (t_data.getMIntA() > 10) {

  } else {
  }
  return 0;
}

int b(Data t_data) {
  t_data.dot_prod_matrix_float_to_b();
  t_data.prod_matrix_float_to_b();
  return 0;
}

int boolean_application(Data t_data) {
  t_data.random_float_a();
  if (t_data.getMFloatA() > 0) {
    a(t_data);
  } else {
    b(t_data);
  }

  return 0;
}


template <typename... FArgs, typename... Args>
void run_callback(std::function<void(FArgs...)> const &func, Args &&... as) {
  func(std::forward<Args>(as)...);
}

template <typename... FArgs, typename... Args>
int branch(
    std::vector<std::tuple<std::function<void(FArgs...)> const &, Args &&...>>
        methods,
    std::tuple<std::function<bool(FArgs...)> const &, Args &&...>
        branch_condidition,
    std::vector<std::tuple<std::function<void(FArgs...)> const &, Args &&...>>
        if_branch,
    std::vector<std::tuple<std::function<void(FArgs...)> const &, Args &&...>>
        else_branch) {

  for (auto method : methods) {
    run_callback(method[0], method[1]);
  }

  if (run_callback(branch_condidition[0], branch_condidition[1])) {

    for (auto method : if_branch) {
      run_callback(method[0], method[1]);
    }
  } else {

    for (auto method : else_branch) {
      run_callback(method[0], method[1]);
    }
  }
  return 0;
}



int boolean_application_template(Data t_data) {
  auto methods = std::vector<std::tuple<std::function<void ()> const &, >>;

  branch();

  t_data.random_float_a();
  if (t_data.getMFloatA() > 0) {
    a(t_data);
  } else {
    b(t_data);
  }

  return 0;
}
