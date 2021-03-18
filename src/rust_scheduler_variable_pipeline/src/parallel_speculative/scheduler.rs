use crate::parallel_speculative::master::master;
use crate::parallel_speculative::slave::slave;
use crate::sequential::data::Data;
use crossbeam_channel::unbounded;
use crossbeam_utils::thread;
use std::sync::{Arc, RwLock};

use rayon::prelude::*;

pub fn data() -> Vec<Arc<RwLock<Data>>> {
    let d: Vec<Arc<RwLock<Data>>> = (0..10000)
        .into_par_iter()
        .map(|_| Arc::new(RwLock::new(Data::new(1000, 1000, 1000))))
        .collect::<Vec<Arc<RwLock<Data>>>>();
    d
}

pub fn scheduler(
    dataset: &mut Arc<RwLock<Data>>,
    improved: bool,
    n_threads: usize,
    pipeline: usize,
    io: bool,
) {
    thread::scope(|scope| {
        let (sender, receiver) = unbounded();
        let (sender2, receiver2) = unbounded();

        for _ in 0..n_threads {
            let (s, r) = (sender2.clone(), receiver.clone());
            let d = dataset.to_owned();
            scope.spawn(move |_| slave(r, s, d, pipeline, io));
        }

        scope.spawn(move |_| master(receiver2, sender, io, pipeline));
    })
    .unwrap();

    //thread::spawn(|| slave(receiver, sender2, dataset.clone()));
}
