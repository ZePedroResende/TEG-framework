use crate::parallel_speculative::pipeline::{prop1, prop2, prop3, prop4, Prop};
use lazy_static::lazy_static;
use std::collections::HashMap;

macro_rules! hashmap {
    ($( $key: expr => $val: expr ),*) => {{
         let mut map = ::std::collections::HashMap::new();
         $( map.insert($key, $val); )*
         map
    }}
}

lazy_static! {
    pub static ref DEPENDENCY_MAP: HashMap<i32, bool> =
        [(2, false), (3, false), (4, true), (5, false)]
            .iter()
            .cloned()
            .collect();
}

lazy_static! {
    pub static ref FLOW_MAP: HashMap<i32, Vec<i32>> = hashmap![
    2 => vec!(3, 5),
    3 => vec!(4, 5),
    4 => vec!(),
    5 => vec!()];
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

lazy_static! {
    pub static ref FUNCTION_IDS: HashMap<&'static str, i32> =
        [("prop1", 2), ("prop2", 3), ("prop3", 4), ("prop4", 5)]
            .iter()
            .cloned()
            .collect();
}
