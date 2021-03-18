use crate::sequential::data::Data;
use crossbeam_channel::{Receiver, RecvError, Sender};
use std::sync::{Arc, RwLock};

pub fn slave(
    receiver: Receiver<i32>,
    sender: Sender<(i32, i32)>,
    dataset: Arc<RwLock<Data>>,
    pipeline: usize,
    io: bool,
) {
    loop {
        let next = match receiver.recv() {
            Ok(next) => next,
            Err(RecvError) => {
                break;
            }
        };

        loop {
            if let Ok(mut data) = dataset.write() {
                let ret = if io {
                    match pipeline {
                        20 => crate::io_pipeline_20::TEG[&next](&mut data),
                        _ => crate::io_pipeline_10::TEG[&next](&mut data),
                    }
                } else {
                    match pipeline {
                        20 => crate::cpu_pipeline_20::TEG[&next](&mut data),
                        _ => crate::cpu_pipeline_10::TEG[&next](&mut data),
                    }
                };

                sender.send((next, ret)).unwrap();
                break;
            }
        }
    }
}
