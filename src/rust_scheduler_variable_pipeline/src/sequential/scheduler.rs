use crate::sequential::data::{dot_prod_matrix, dot_prod_matrix_float, Data};
use lazy_static::lazy_static;
use std::collections::HashMap;

type Prop = for<'r> fn(&'r mut Data) -> i32;

fn prop1(data: &mut Data) -> i32 {
    let a = data.m_int_a;
    let b = data.m_int_b;
    let c = data.m_int_c;
    let d = data.m_list_ints[0];

    if a == 1 && b > 1 {
        return 3;
    }

    if b + 1 > 0 {
        if ((c + 1) != 0) && d == 1 {
            return 4;
        }

        return 3;
    }
    return 1;
}
fn prop2(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    if true {
        if true {
            //logger::instance().log("prop3");
            return 4;
        } else {
            //logger::instance().log("prop4");
            return 5;
        }
    }

    return 0;
}

fn prop3(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    data.m_matrix_a = d3.to_vec();

    //logger::instance().log("Running the prop3");
    return 1;
}

fn prop4(data: &mut Data) -> i32 {
    let a = 1;

    let d1 = data.m_matrix_float_a.as_mut();
    let d2 = data.m_matrix_float_c.as_mut();
    let d3 = data.m_matrix_float_b.as_mut();

    dot_prod_matrix_float(d3, d1, d2);
    dot_prod_matrix_float(d1, d2, d3);
    dot_prod_matrix_float(d3, d2, d1);
    dot_prod_matrix_float(d3, d1, d2);

    data.m_matrix_float_b = d3.to_vec();
    if a > 0 {
        return 0;
    }
    return 1;
}

lazy_static! {
    pub static ref TEG: HashMap<i32, Prop> = [
        (2, prop1 as Prop),
        (3, prop2 as Prop),
        (4, prop3 as Prop),
        (5, prop4 as Prop),
    ]
    .iter()
    .cloned()
    .collect();
}

pub fn scheduler(data: &mut Data, pipeline: usize, io: bool) -> i32 {
    if io {
        match pipeline {
            20 => crate::io_pipeline_20::scheduler(data),
            _ => crate::io_pipeline_10::scheduler(data),
        }
    } else {
        match pipeline {
            20 => crate::cpu_pipeline_20::scheduler(data),
            _ => crate::cpu_pipeline_10::scheduler(data),
        }
    }
}
