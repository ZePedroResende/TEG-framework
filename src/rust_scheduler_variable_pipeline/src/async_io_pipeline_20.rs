#[allow(dead_code)]
use crate::native::data::Data;
use async_recursion::async_recursion;
use async_std::fs::File;
use async_std::io;
use async_std::prelude::*;

async fn prop1(data: &mut Data) -> io::Result<i32> {
    let a = data.m_int_a;
    let b = data.m_int_b;
    let c = data.m_int_c;
    let d = data.m_list_ints[0];

    if a == 1 && b > 1 {
        return Ok(3);
    }

    if b + 1 > 0 {
        if ((c + 1) != 0) && d == 1 {
            return Ok(4);
        }

        return Ok(3);
    }
    return Ok(1);
}
async fn prop2(data: &mut Data) -> io::Result<i32> {
    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();

    let mut file = File::create("/tmp/foo.txt").await?;
    for i in d1.iter() {
        for j in i.iter() {
            file.write_all(&j.to_ne_bytes()).await?;
        }
    }

    if true {
        if true {
            //logger::instance().log("prop3");
            return Ok(4);
        } else {
            //logger::instance().log("prop4");
            return Ok(5);
        }
    }

    return Ok(0);
}

async fn prop3(data: &mut Data) -> io::Result<i32> {
    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();

    let mut file = File::create("/tmp/foo.txt").await?;
    for i in d1.iter() {
        for j in i.iter() {
            file.write_all(&j.to_ne_bytes()).await?;
        }
    }

    //logger::instance().log("Running the prop3");
    return Ok(1);
}

async fn prop4(data: &mut Data) -> io::Result<i32> {
    let a = 1;

    let d1: &Vec<Vec<i32>> = data.m_matrix_a.as_mut();
    let mut file = File::open("/tmp/foo.txt").await?;
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).await?;

    for i in d1.iter() {
        for j in i.iter() {
            file.write_all(&j.to_ne_bytes()).await?;
        }
    }

    if a > 0 {
        return Ok(0);
    }
    return Ok(1);
}

pub async fn pipeline_async(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        Ok(3) => define_prop2(data).await,
        Ok(4) => define_prop3(data).await,
        _ => define_prop5(data).await,
    }
}

//async fn define_prop1(data: &mut Data) -> io::Result<i32> {}

#[async_recursion]
async fn define_prop2(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop3(data).await,
        Ok(5) => define_prop4(data).await,
        _ => define_prop5(data).await,
    }
}

#[async_recursion]
async fn define_prop3(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(_x) => define_prop5(data).await,
        _ => define_prop5(data).await,
    }
}

#[async_recursion]
async fn define_prop4(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(_x) => define_prop5(data).await,
        _ => define_prop5(data).await,
    }
}

#[async_recursion]
async fn define_prop5(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        Ok(3) => define_prop2(data).await,
        Ok(4) => define_prop3(data).await,
        _ => define_prop9(data).await,
    }
}

#[async_recursion]
async fn define_prop6(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop3(data).await,
        Ok(5) => define_prop4(data).await,
        _ => define_prop9(data).await,
    }
}

#[async_recursion]
async fn define_prop7(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(x) => x,
        _ => define_prop9(data).await,
    }
}

#[async_recursion]
async fn define_prop8(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(x) => x,
        _ => define_prop9(data).await,
    }
}

#[async_recursion]
pub async fn define_prop9(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        Ok(3) => define_prop10(data).await,
        Ok(4) => define_prop11(data).await,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
async fn define_prop10(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop11(data).await,
        Ok(5) => define_prop12(data).await,
        _ => define_prop19(data).await,
    }
}

#[async_recursion]
async fn define_prop11(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(x) => x,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
async fn define_prop12(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(x) => x,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
pub async fn define_prop13(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        Ok(3) => define_prop14(data).await,
        Ok(4) => define_prop15(data).await,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
async fn define_prop14(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop15(data).await,
        Ok(5) => define_prop16(data).await,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
async fn define_prop15(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(x) => x,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
async fn define_prop16(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(x) => x,
        _ => define_prop20(data).await,
    }
}

#[async_recursion]
pub async fn define_prop17(data: &mut Data) -> i32 {
    //println!("prop1");
    match prop1(data).await {
        Ok(3) => define_prop18(data).await,
        Ok(4) => define_prop19(data).await,
        _ => 1,
    }
}

#[async_recursion]
async fn define_prop18(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop19(data).await,
        Ok(5) => define_prop20(data).await,
        _ => 0,
    }
}

#[async_recursion]
async fn define_prop19(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(x) => x,
        _ => 1,
    }
}

#[async_recursion]
async fn define_prop20(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(x) => x,
        _ => 1,
    }
}
