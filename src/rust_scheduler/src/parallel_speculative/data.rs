#![allow(non_snake_case)]
use rand::{thread_rng, Rng};
macro_rules! pub_struct {
    ($name:ident {$($field:ident: $t:ty,)*}) => {
        #[derive(Debug, Clone, PartialEq)] // ewww
        pub struct $name {
            $(pub $field: $t),*
        }
    }
}

pub_struct!( Data {
    m_vector_float_a: Vec<f32>,
    m_vector_float_b: Vec<f32>,
    m_vector_float_c: Vec<f32>,
    m_vector_int_a: Vec<i32>,
    m_vector_int_b: Vec<i32>,
    m_vector_int_c: Vec<i32>,
    m_matrix_a: Vec<Vec<i32>>,
    m_matrix_b: Vec<Vec<i32>>,
    m_matrix_c: Vec<Vec<i32>>,
    m_matrix_float_a: Vec<Vec<f32>>,
    m_matrix_float_b: Vec<Vec<f32>>,
    m_matrix_float_c: Vec<Vec<f32>>,
    m_int_a: i32,
    m_int_b: i32,
    m_int_c: i32,
    m_float_a: f32,
    m_float_b: f32,
    m_float_c: f32,
    m_list_ints: Vec<i32>,
    m_list_floats: Vec<f32>,

    VEC_SIZE: i32,
    MATRIX_SIZE: i32,
    LIST_SIZE: i32,
});

impl Data {
    pub fn new(VEC_SIZE: i32, MATRIX_SIZE: i32, LIST_SIZE: i32) -> Data {
        Data {
            m_vector_float_a: fill_vector_float(VEC_SIZE),
            m_vector_float_b: fill_vector_float(VEC_SIZE),
            m_vector_float_c: fill_vector_float(VEC_SIZE),
            m_vector_int_a: fill_vector(VEC_SIZE),
            m_vector_int_b: fill_vector(VEC_SIZE),
            m_vector_int_c: fill_vector(VEC_SIZE),
            m_matrix_a: fill_matrix(MATRIX_SIZE),
            m_matrix_b: fill_matrix(MATRIX_SIZE),
            m_matrix_c: fill_matrix(MATRIX_SIZE),
            m_matrix_float_a: fill_matrix_float(MATRIX_SIZE),
            m_matrix_float_b: fill_matrix_float(MATRIX_SIZE),
            m_matrix_float_c: fill_matrix_float(MATRIX_SIZE),
            m_int_a: 1,
            m_int_b: 2,
            m_int_c: 3,
            m_float_a: 1.0,
            m_float_b: 2.0,
            m_float_c: 3.0,
            m_list_ints: fill_vector(LIST_SIZE),
            m_list_floats: fill_vector_float(LIST_SIZE),
            VEC_SIZE,
            MATRIX_SIZE,
            LIST_SIZE,
        }
    }
}

pub fn prod_matrix(a: &mut Vec<Vec<i32>>, b: &mut Vec<Vec<i32>>, c: &mut Vec<Vec<i32>>) {
    let height = a.len();
    let width = a[0].len();

    for i in 0..height {
        for j in 0..width {
            a[i][j] = 0;

            for k in 0..width {
                a[i][j] += b[i][k] * c[k][j];
            }
        }
    }
}

pub fn prod_matrix_float(a: &mut Vec<Vec<f32>>, b: &mut Vec<Vec<f32>>, c: &mut Vec<Vec<f32>>) {
    let height = a.len();
    let width = a[0].len();

    for i in 0..height {
        for j in 0..width {
            a[i][j] = 0.0;

            for k in 0..width {
                a[i][j] += b[i][k] * c[k][j];
            }
        }
    }
}

pub fn dot_prod_matrix(a: &mut Vec<Vec<i32>>, b: &mut Vec<Vec<i32>>, c: &mut Vec<Vec<i32>>) {
    let height = a.len();
    let width = a[0].len();

    for i in 0..height {
        for j in 0..width {
            a[i][j] = b[i][j] * c[i][j];
        }
    }
}

pub fn dot_prod_matrix_float(a: &mut Vec<Vec<f32>>, b: &mut Vec<Vec<f32>>, c: &mut Vec<Vec<f32>>) {
    let height = a.len();
    let width = a[0].len();

    for i in 0..height {
        for j in 0..width {
            a[i][j] = b[i][j] * c[i][j];
        }
    }
}

fn fill_matrix(matrix_size: i32) -> Vec<Vec<i32>> {
    let mut rng = thread_rng();
    let numbers: Vec<Vec<i32>> = (0..matrix_size)
        .map(|_| (0..matrix_size).map(|_| rng.gen_range(-10..10)).collect())
        .collect();
    numbers
}

fn fill_matrix_float(matrix_size: i32) -> Vec<Vec<f32>> {
    let mut rng = thread_rng();
    let numbers: Vec<Vec<f32>> = (0..matrix_size)
        .map(|_| {
            (0..matrix_size)
                .map(|_| rng.gen_range(-100.0..100.0))
                .collect()
        })
        .collect();
    numbers
}

fn fill_vector(list_size: i32) -> Vec<i32> {
    let mut rng = thread_rng();
    let numbers: Vec<i32> = (0..list_size).map(|_| rng.gen_range(-100..100)).collect();
    numbers
}

fn fill_vector_float(list_size: i32) -> Vec<f32> {
    let mut rng = thread_rng();
    let numbers: Vec<f32> = (0..list_size)
        .map(|_| rng.gen_range(-100.0..100.0))
        .collect();
    numbers
}

impl Default for Data {
    fn default() -> Data {
        Data::new(10, 10, 10)
    }
}
