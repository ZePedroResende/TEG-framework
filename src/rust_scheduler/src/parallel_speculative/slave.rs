use crate::parallel_speculative::data::Data;
use crate::parallel_speculative::utils::TEG;
use crossbeam_channel::{Receiver, RecvError, Sender};
use std::sync::{Arc, RwLock};

pub fn slave(receiver: Receiver<i32>, sender: Sender<(i32, i32)>, dataset: Arc<RwLock<Data>>) {
    loop {
        let next = match receiver.recv() {
            Ok(next) => next,
            Err(RecvError) => {
                break;
            }
        };

        loop {
            if let Ok(mut data) = dataset.write() {
                let ret = TEG[&next](&mut data);

                sender.send((next, ret)).unwrap();
                break;
            }
        }
    }
}
