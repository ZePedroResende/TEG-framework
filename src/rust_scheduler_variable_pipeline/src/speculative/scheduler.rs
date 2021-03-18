use crate::sequential::data::Data;
use crate::speculative::master::master;
use crate::speculative::slave::slave;
use crossbeam_channel::unbounded;
use crossbeam_utils::thread;
use std::sync::{Arc, RwLock};
use std::time::SystemTime;

pub fn scheduler(dataset: Arc<RwLock<Vec<Data>>>, n_threads: usize, pipeline: usize, io: bool) {
    let (sender, receiver) = unbounded();
    let (sender2, receiver2) = unbounded();
    //  let now = SystemTime::now();
    thread::scope(|scope| {
        for id in 0..n_threads {
            let (s, r) = (sender2.clone(), receiver.clone());
            let d = dataset.clone();
            scope.spawn(move |_| slave(r, s, d, pipeline, io, id));
        }

        scope.spawn(move |_| master(receiver2, sender, dataset, io, pipeline));
    })
    .unwrap();

    //    let c = now.elapsed().unwrap();
    //   println!("{:?}", c);
    //master(receiver2, sender, dataset.clone(), io, pipeline);
    //thread::spawn(|| slave(receiver, sender2, dataset.clone()));
}
