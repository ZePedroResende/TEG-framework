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
    return 6;
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

    return 6;
}

fn prop3(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    for _ in 0..1000 {
        dot_prod_matrix(d3, d1, d2);
        dot_prod_matrix(d1, d2, d3);
        dot_prod_matrix(d3, d1, d2);
    }

    data.m_matrix_a = d3.to_vec();

    //logger::instance().log("Running the prop3");
    return 6;
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
        return 6;
    }
    return 6;
}

fn prop5(data: &mut Data) -> i32 {
    let a = data.m_int_a;
    let b = data.m_int_b;
    let c = data.m_int_c;
    let d = data.m_list_ints[0];

    if a == 1 && b > 1 {
        return 7;
    }

    if b + 1 > 0 {
        if ((c + 1) != 0) && d == 1 {
            return 8;
        }

        return 7;
    }
    return 10;
}
fn prop6(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    for _ in 0..1000 {
        dot_prod_matrix(d3, d1, d2);
        dot_prod_matrix(d1, d2, d3);
        dot_prod_matrix(d3, d1, d2);
    }

    if true {
        if true {
            //logger::instance().log("prop3");
            return 8;
        } else {
            //logger::instance().log("prop4");
            return 9;
        }
    }

    return 10;
}

fn prop7(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    data.m_matrix_a = d3.to_vec();

    //logger::instance().log("Running the prop3");
    return 10;
}

fn prop8(data: &mut Data) -> i32 {
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
        return 10;
    }
    return 10;
}

fn prop9(data: &mut Data) -> i32 {
    let a = data.m_int_a;
    let b = data.m_int_b;
    let c = data.m_int_c;
    let d = data.m_list_ints[0];

    if a == 1 && b > 1 {
        return 11;
    }

    if b + 1 > 0 {
        if ((c + 1) != 0) && d == 1 {
            return 12;
        }

        return 11;
    }
    return 1;
}
fn prop10(data: &mut Data) -> i32 {
    let d1 = data.m_matrix_a.as_mut();
    let d2 = data.m_matrix_b.as_mut();
    let d3 = data.m_matrix_c.as_mut();

    dot_prod_matrix(d3, d1, d2);
    dot_prod_matrix(d1, d2, d3);
    dot_prod_matrix(d3, d1, d2);

    if true {
        if true {
            //logger::instance().log("prop3");
            return 13;
        } else {
            //logger::instance().log("prop4");
            return 12;
        }
    }

    return 0;
}

fn prop11(data: &mut Data) -> i32 {
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

fn prop12(data: &mut Data) -> i32 {
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

macro_rules! hashmap {
    ($( $key: expr => $val: expr ),*) => {{
         let mut map = ::std::collections::HashMap::new();
         $( map.insert($key, $val); )*
         map
    }}
}

lazy_static! {
    pub static ref TEG: HashMap<i32, Prop> = [
        (2, prop1 as Prop),
        (3, prop2 as Prop),
        (4, prop3 as Prop),
        (5, prop4 as Prop),
        (6, prop5 as Prop),
        (7, prop6 as Prop),
        (8, prop7 as Prop),
        (9, prop8 as Prop),
        (10, prop9 as Prop),
        (11, prop10 as Prop),
        (12, prop11 as Prop),
        (13, prop12 as Prop),
    ]
    .iter()
    .cloned()
    .collect();
}

lazy_static! {
    pub static ref DEPENDENCY_MAP: HashMap<i32, bool> = [
        (2, false),
        (3, false),
        (4, false),
        (5, false),
        (6, false),
        (7, false),
        (8, false),
        (9, false),
        (10, false),
        (11, false),
        (12, false),
        (13, false),
    ]
    .iter()
    .cloned()
    .collect();
}

lazy_static! {
    pub static ref FLOW_MAP: HashMap<i32, Vec<i32>> = hashmap![
    2 => vec!(3, 5, 6),
    3 => vec!(4, 5, 6),
    4 => vec!(6),
    5 => vec!(6),

    6 => vec!(7, 9,10),
    7 => vec!(8, 9,10),
    8 => vec!(10),
    9 => vec!(10),

    10 => vec!(11, 13),
    11=> vec!(12, 13),
    12 => vec!(),
    13 => vec!()
    ];
}

pub fn flow_map(function_id: i32) -> Vec<i32> {
    FLOW_MAP[&function_id].clone()
}

pub fn dependency_map(function_id: i32) -> bool {
    DEPENDENCY_MAP[&function_id]
}

pub fn calculate(data: &mut Data, result: i32) -> i32 {
    TEG[&result](data)
}
pub fn scheduler(data: &mut Data) -> i32 {
    let mut result = 2;

    while result > 1 {
        result = TEG[&result](data);
    }

    result
}
