use crate::speculative::data::Data;
use crate::speculative::io_utils::TEG;
use crossbeam_channel::{Receiver, Sender};
use std::sync::{Arc, RwLock};

fn is_empty(dataset: Arc<RwLock<Vec<Data>>>) -> bool {
    loop {
        if let Ok(read_lock) = dataset.read() {
            return (*read_lock).is_empty().clone();
        }
    }
}

pub fn io_slave(
    receiver: Receiver<i32>,
    sender: Sender<(i32, i32)>,
    dataset: Arc<RwLock<Vec<Data>>>,
) {
    let mut data_ref;
    while !is_empty(dataset.clone()) {
        match receiver.try_recv() {
            Ok(next) => loop {
                if let Ok(mut write_lock) = dataset.write() {
                    data_ref = (*write_lock).first_mut().unwrap();

                    let ret = TEG[&next](data_ref);

                    sender.send((next, ret)).unwrap();
                    break;
                }
            },

            _ => (),
        }
    }
}
