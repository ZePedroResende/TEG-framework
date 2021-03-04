use rayon::prelude::*;
use rust_scheduler::parallel_speculative::data::Data;
use rust_scheduler::parallel_speculative::scheduler::scheduler;
use std::sync::{Arc, RwLock};
use std::time::SystemTime;
//use tokio::sync::oneshot;

fn main() {
    /*
    let data: Vec<Arc<RwLock<Data>>> = (0..500)
        .into_par_iter()
        .map(|_| Arc::new(RwLock::new(Data::new(1000, 2000, 1000))))
        .collect::<Vec<Arc<RwLock<Data>>>>();
    */

    let data: Vec<Data> = (0..200)
        .into_par_iter()
        .map(|_| Data::new(1000, 2000, 1000))
        .collect::<Vec<Data>>();

    println!("Started");
    let now = SystemTime::now();
    let _a: Vec<_> = data
        .into_par_iter()
        .map(move |d| scheduler(&mut Arc::new(RwLock::new(d)), true))
        .collect();
    let a = now.elapsed().unwrap();
    println!("{:?}", a);

    /*
    let data2: Vec<Arc<RwLock<Data>>> = (0..10)
        .into_par_iter()
        .map(|_| Arc::new(RwLock::new(Data::new(1000, 2000, 1000))))
        .collect::<Vec<Arc<RwLock<Data>>>>();
    let now2 = SystemTime::now();
    let _a: Vec<_> = data2
        .into_iter()
        .map(|mut d| scheduler(&mut d, true))
        .collect();
    let b = now2.elapsed().unwrap();

    println!("{:?}", b);
    */
}
