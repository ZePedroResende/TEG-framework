use crate::sequential::data::Data;
use crossbeam_channel::{Receiver, Sender};
use std::sync::{Arc, RwLock};
use std::time::SystemTime;

fn is_empty(dataset: Arc<RwLock<Vec<Data>>>) -> bool {
    loop {
        if let Ok(read_lock) = dataset.read() {
            return (*read_lock).is_empty().clone();
        }
    }
}

pub fn slave(
    receiver: Receiver<i32>,
    sender: Sender<(i32, i32)>,
    dataset: Arc<RwLock<Vec<Data>>>,
    pipeline: usize,
    io: bool,
    id: usize,
) {
    //let mut data_ref;
    //while !is_empty(dataset.clone()) {
    loop {
        //let now = SystemTime::now();
        let next = match receiver.recv() {
            Ok(next) => next,

            _ => break,
        };

        loop {
            if let Ok(write_lock) = dataset.read() {
                let mut d = (*write_lock).clone();
                match d.first_mut() {
                    Some(data_ref) => {
                        let ret = if io {
                            match pipeline {
                                20 => crate::io_pipeline_20::calculate(data_ref, next),
                                _ => crate::io_pipeline_10::calculate(data_ref, next),
                            }
                        } else {
                            match pipeline {
                                20 => crate::cpu_pipeline_20::calculate(data_ref, next),
                                _ => crate::cpu_pipeline_10::calculate(data_ref, next),
                            }
                        };

                        sender.send((next, ret)).unwrap();
                        //let c = now.elapsed().unwrap();
                        //println!("slave => {:?}", c);
                        break;
                    }

                    None => break,
                }
            }
        }
    }
}
