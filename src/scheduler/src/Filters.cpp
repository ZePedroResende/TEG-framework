//
// Created by resende on 11/27/19.
//
#include "Data.hpp"

bool prod_matrix_int_to_a(Data t_data) { return true; }
bool prod_matrix_int_to_b(Data t_data) { return true; }
bool prod_matrix_int_to_c(Data t_data) { return true; }

bool dot_prod_matrix_int_to_a(Data t_data) { return true; }
bool dot_prod_matrix_int_to_b(Data t_data) { return true; }
bool dot_prod_matrix_int_to_c(Data t_data) { return true; }

bool prod_matrix_float_to_a(Data t_data) { return true; }
bool prod_matrix_float_to_b(Data t_data) { return true; }
bool prod_matrix_float_to_c(Data t_data) { return true; }

bool dot_prod_matrix_float_to_a(Data t_data) { return true; }
bool dot_prod_matrix_float_to_b(Data t_data) { return true; }
bool dot_prod_matrix_float_to_c(Data t_data) { return true; }

bool vector_matrix_int_to_a(Data t_data) { return true; }
bool vector_matrix_int_to_b(Data t_data) { return true; }
bool vector_matrix_int_to_c(Data t_data) { return true; }

bool vector_matrix_float_to_a(Data t_data) { return true; }
bool vector_matrix_float_to_b(Data t_data) { return true; }
bool vector_matrix_float_to_c(Data t_data) { return true; }

bool is_int_a_positive(Data t_data) { return t_data.getMIntA() > 0; }
bool is_int_b_positive(Data t_data) { return t_data.getMIntB() > 0; }
bool is_int_c_positive(Data t_data) { return t_data.getMIntC() > 0; }

bool is_float_a_positive(Data t_data) { return t_data.getMFloatA() > 0; }
bool is_float_b_positive(Data t_data) { return t_data.getMFloatB() > 0; }
bool is_float_c_positive(Data t_data) { return t_data.getMFloatC() > 0; }

bool add_int_a(Data t_data) { return t_data.getMIntA() > 0; }
bool add_int_b(Data t_data) { return t_data.getMIntB() > 0; }
bool add_int_c(Data t_data) { return t_data.getMIntC() > 0; }

bool add_float_a(Data t_data) { return t_data.getMFloatA() > 0; }
bool add_float_b(Data t_data) { return t_data.getMFloatB() > 0; }
bool add_float_c(Data t_data) { return t_data.getMFloatC() > 0; }

bool filter_list_int(Data t_data)_ { return true; }
bool filter_list_float(Data t_data)_ { return true; }

bool random_matrix_int_to_a(Data t_data) { return true; }
bool random_matrix_int_to_b(Data t_data) { return true; }
bool random_matrix_int_to_c(Data t_data) { return true; }

bool random_matrix_float_to_a(Data t_data) { return true; }
bool random_matrix_float_to_b(Data t_data) { return true; }
bool random_matrix_float_to_c(Data t_data) { return true; }

bool random_list_int(Data t_data)_ { return true; }
bool random_list_float(Data t_data)_ { return true; }

bool random_int_a(Data t_data) { return t_data.getMIntA() > 0; }
bool random_int_b(Data t_data) { return t_data.getMIntB() > 0; }
bool random_int_c(Data t_data) { return t_data.getMIntC() > 0; }

bool random_float_a(Data t_data) { return t_data.getMFloatA() > 0; }
bool random_float_b(Data t_data) { return t_data.getMFloatB() > 0; }
bool random_float_c(Data t_data) { return t_data.getMFloatC() > 0; }
