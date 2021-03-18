//use rayon::prelude::*;
use rust_scheduler::sequential::data::Data;
use rust_scheduler::sequential::scheduler::scheduler;
//use tokio::sync::oneshot;
use std::time::SystemTime;

fn main() {
    let d: Vec<Data> = (0..10)
        .into_iter()
        .map(|_| Data::new(1000, 1000, 1000))
        .collect::<Vec<Data>>();

    let now = SystemTime::now();
    let a: Vec<_> = d
        .into_iter()
        .map(|mut d| scheduler(&mut d, 20, false))
        .collect();

    let c = now.elapsed().unwrap();
    println!("{:?}", c);
}
