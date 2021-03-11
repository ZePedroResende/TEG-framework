use crate::speculative::data::Data;
use crate::speculative::io_slave::io_slave;
use crate::speculative::master::master;
use crate::speculative::slave::slave;
use crossbeam_channel::unbounded;
use crossbeam_utils::thread;
use std::sync::{Arc, RwLock};

pub fn io_scheduler(dataset: Arc<RwLock<Vec<Data>>>, improved: bool, n_threads: usize) {
    let (sender, receiver) = unbounded();
    let (sender2, receiver2) = unbounded();

    thread::scope(|scope| {
        for _ in 0..n_threads {
            let (s, r) = (sender2.clone(), receiver.clone());
            let d = dataset.clone();
            scope.spawn(move |_| io_slave(r, s, d));
        }

        let (s, r) = (sender.clone(), receiver2.clone());
        let d = dataset.clone();
        scope.spawn(move |_| master(r, s, d, improved));
    })
    .unwrap();

    //thread::spawn(|| slave(receiver, sender2, dataset.clone()));
}
pub fn scheduler(dataset: Arc<RwLock<Vec<Data>>>, improved: bool, n_threads: usize) {
    let (sender, receiver) = unbounded();
    let (sender2, receiver2) = unbounded();

    thread::scope(|scope| {
        for _ in 0..n_threads {
            let (s, r) = (sender2.clone(), receiver.clone());
            let d = dataset.clone();
            scope.spawn(move |_| slave(r, s, d));
        }

        let (s, r) = (sender.clone(), receiver2.clone());
        let d = dataset.clone();
        scope.spawn(move |_| master(r, s, d, improved));
    })
    .unwrap();

    //thread::spawn(|| slave(receiver, sender2, dataset.clone()));
}
