use rayon::prelude::*;
use rust_scheduler::native::data::Data;
use rust_scheduler::native::scheduler::scheduler;
use std::sync::mpsc::channel;

type Result<T> = std::result::Result<T, Box<dyn std::error::Error + Send + Sync>>;

#[tokio::main]
async fn main() -> Result<()> {
    let d: Vec<Data> = (0..10)
        .into_par_iter()
        .map(|_| Data::new(1000, 1000, 1000))
        .collect::<Vec<Data>>();
    let (sender, receiver) = channel();
    //scheduler(d.first().unwrap().clone());

    let _a: Vec<_> = d
        .into_par_iter()
        .map_with(sender, |s, mut data| s.send(scheduler(&mut data)))
        .collect();

    let b: Vec<_> = receiver.iter().collect();

    println!("{:?}", b);

    Ok(())
}
