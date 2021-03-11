#[allow(dead_code)]
use crate::native::data::{dot_prod_matrix, dot_prod_matrix_float, Data};
use crate::native::pipeline_async::pipeline_async;
use crate::native::pipeline_tokio::pipeline_tokio;
use futures::executor::block_on;
//use futures::future::Then;
//use futures::{future, Future, Then FutureExt};

async fn prop1(data: &mut Data) -> i32 {
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
async fn prop2(data: &mut Data) -> i32 {
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

async fn prop3(data: &mut Data) -> i32 {
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

async fn prop4(data: &mut Data) -> i32 {
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

async fn pipeline(data: &mut Data) -> i32 {
    define_prop1(data).await
}

async fn define_prop1(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        3 => define_prop2(data).await,
        4 => define_prop3(data).await,
        _ => 1,
    }
}

async fn define_prop2(data: &mut Data) -> i32 {
    match prop2(data).await {
        4 => define_prop3(data).await,
        5 => define_prop4(data).await,
        _ => 0,
    }
}

async fn define_prop3(data: &mut Data) -> i32 {
    prop3(data).await
}

async fn define_prop4(data: &mut Data) -> i32 {
    prop4(data).await
}

/*
macro_rules! hashmap {
    ($( $key: expr => $val: expr ),*) => {{
         let mut map = ::std::collections::HashMap::new();
         $( map.insert($key, $val); )*
         map
    }}
}
*/

pub fn scheduler(data: &mut Data) -> i32 {
    /*
    let teg: HashMap<i32, &str> = [(3, "prop2"), (4, "prop3"), (5, "prop4")]
        .iter()
        .cloned()
        .collect();
    let dependency_map: HashMap<&str, bool> = [
        ("Prop1", false),
        ("Prop2", false),
        ("Prop3", true),
        ("Prop4", false),
    ]

    .iter()
    .cloned()
    .collect();

    let flow_map: HashMap<&str, Vec<&str>> = hashmap![
    "Prop1" => vec!("Prop2", "Prop4"),
    "Prop2" => vec!("Prop3", "Prop4"),
    "Prop3" => vec!(),
    "Prop4" => vec!()];

    */
    //println!("{:?}", teg);
    //println!("{:?}", dependency_map);
    //println!("{:?}", flow_map);

    block_on(pipeline(data));
    //    println!("result : {}", result);

    1
}
