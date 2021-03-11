use crate::sequential::data::{dot_prod_matrix, dot_prod_matrix_float, Data};
use lazy_static::lazy_static;
use std::collections::HashMap;

type Prop = for<'r> fn(&'r mut Data) -> i32;

use std::fs::File;
use std::io::prelude::*;

pub fn prop1(data: &mut Data) -> i32 {
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
pub fn prop2(data: &mut Data) -> i32 {
    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();

    let mut file = File::create("/tmp/foo.txt").unwrap();
    for i in d1.iter() {
        for j in i.iter() {
            file.write_all(&j.to_ne_bytes()).unwrap();
        }
    }

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

pub fn prop3(data: &mut Data) -> i32 {
    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();

    let mut file = File::create("/tmp/foo.txt").unwrap();
    for i in d1.iter() {
        for j in i.iter() {
            file.write_all(&j.to_ne_bytes()).unwrap();
        }
    }

    //logger::instance().log("Running the prop3");
    return 1;
}

pub fn prop4(data: &mut Data) -> i32 {
    let a = 1;

    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();
    let mut file = File::create("/tmp/foo.txt").unwrap();
    let mut buffer = Vec::new();
    let thingy = file.read_to_end(&mut buffer);
    match thingy {
        Ok(s) => s,
        Err(_) => 0,
    };

    for i in d1.iter() {
        for j in i.iter() {
            match file.write_all(&j.to_ne_bytes()) {
                Ok(..) => {}
                Err(e) => println!("{}", e),
            }
        }
    }

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

pub fn io_scheduler(data: &mut Data) -> i32 {
    let teg: HashMap<i32, Prop> = [
        (2, prop1 as Prop),
        (3, prop2 as Prop),
        (4, prop3 as Prop),
        (5, prop4 as Prop),
    ]
    .iter()
    .cloned()
    .collect();

    let mut result = 2;

    while result > 1 {
        result = teg[&result](data);
    }

    result
}

pub fn scheduler(data: &mut Data) -> i32 {
    let teg: HashMap<i32, Prop> = [
        (2, prop1 as Prop),
        (3, prop2 as Prop),
        (4, prop3 as Prop),
        (5, prop4 as Prop),
    ]
    .iter()
    .cloned()
    .collect();

    let mut result = 2;

    while result > 1 {
        result = teg[&result](data);
    }

    result
}
