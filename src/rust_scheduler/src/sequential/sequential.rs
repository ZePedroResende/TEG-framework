use rayon::prelude::*;
use rust_scheduler::sequential::data::Data;
use rust_scheduler::sequential::scheduler::scheduler;
//use tokio::sync::oneshot;
use std::time::Instant;
fn main() {
    let d: Vec<Data> = (0..600)
        .into_par_iter()
        .map(|_| Data::new(1000, 512, 1000))
        .collect::<Vec<Data>>();

    let a: Vec<_> = d.into_iter().map(|mut d| scheduler(&mut d)).collect();

    println!("{:?}", a);
}
