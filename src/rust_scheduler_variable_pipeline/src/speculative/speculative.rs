//use rayon::prelude::*;
use rust_scheduler::sequential::data::Data;
use rust_scheduler::speculative::scheduler::scheduler;
use std::sync::{Arc, RwLock};
//use tokio::sync::oneshot;
//
use std::time::SystemTime;

fn main() {
    let d: Vec<Data> = (0..10)
        .into_iter()
        .map(|_| Data::new(1000, 1000, 1000))
        .collect::<Vec<Data>>();
    let arc_data = Arc::new(RwLock::new(d));
    let now = SystemTime::now();
    scheduler(arc_data, 2, 20, false);
    let c = now.elapsed().unwrap();
    println!("{:?}", c);
}
