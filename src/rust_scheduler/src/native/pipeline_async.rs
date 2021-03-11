#[allow(dead_code)]
use crate::native::data::Data;
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
        _ => 1,
    }
}

//async fn define_prop1(data: &mut Data) -> io::Result<i32> {}

async fn define_prop2(data: &mut Data) -> i32 {
    match prop2(data).await {
        Ok(4) => define_prop3(data).await,
        Ok(5) => define_prop4(data).await,
        _ => 0,
    }
}

async fn define_prop3(data: &mut Data) -> i32 {
    match prop3(data).await {
        Ok(x) => x,
        _ => 1,
    }
}

async fn define_prop4(data: &mut Data) -> i32 {
    match prop4(data).await {
        Ok(x) => x,
        _ => 1,
    }
}
