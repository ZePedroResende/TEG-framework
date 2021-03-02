use rayon::prelude::*;
use rust_scheduler::speculative::data::Data;
use rust_scheduler::speculative::scheduler::scheduler;
use std::sync::{Arc, RwLock};
//use tokio::sync::oneshot;

fn main() {
    let d: Vec<Data> = (0..10)
        .into_par_iter()
        .map(|_| Data::new(1000, 1000, 1000))
        .collect::<Vec<Data>>();

    scheduler(Arc::new(RwLock::new(d)), true);
}
