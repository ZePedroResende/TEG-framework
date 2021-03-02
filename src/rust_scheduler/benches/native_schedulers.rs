use criterion::{black_box, criterion_group, criterion_main, Criterion};

use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use rust_scheduler::native::data::Data;
use rust_scheduler::native::scheduler::scheduler;
use std::sync::mpsc::channel;
use std::sync::{Arc, RwLock};

// Thanks to the example provided by @jebbow in his article
// https://www.jibbow.com/posts/criterion-flamegraphs/
//
fn tokio_bench(data: &mut Vec<Data>) -> i32 {
    let (sender, receiver) = channel();
    let result = tokio::runtime::Builder::new_multi_thread()
        .enable_all()
        .build()
        .unwrap()
        .block_on(async {
            let _a: Vec<_> = data
                .into_par_iter()
                .map_with(sender, |s, d| s.send(scheduler(d)))
                .collect();

            let b: Vec<_> = receiver.iter().collect();
            b[0]
        });
    result
}

fn sequential_bench(data: &mut Vec<rust_scheduler::sequential::data::Data>) -> i32 {
    let a: Vec<_> = data
        .into_iter()
        .map(|d| rust_scheduler::sequential::scheduler::scheduler(d))
        .collect();

    a[0]
}

fn speculative_bench(data: Arc<RwLock<Vec<rust_scheduler::speculative::data::Data>>>) {
    rust_scheduler::speculative::scheduler::scheduler(data, true);
}

/*
fn tokio_sequential_bench(data: Vec<Data>)-> i32{

    let (sender, receiver) = channel();
 let result = tokio::runtime::Builder::new_multi_thread()
        .enable_all()
        .build()
        .unwrap()
        .block_on( async {

        let _a: Vec<_> = data
            .into_par_iter()
            .map_with(sender, |s, d| s.send(scheduler(d)))
            .collect();

        let b: Vec<_> = receiver.iter().collect();
        b[0]

    }
    );
    result
}
*/

fn size_of_struct(size: usize) -> usize {
    ((std::mem::size_of::<i32>() * size * size * 3)
        + (std::mem::size_of::<f32>() * size * size * 3))
        * 500
}

fn async_bench(data: &mut Vec<Data>) -> i32 {
    let (sender, receiver) = channel();
    //scheduler(d.first().unwrap().clone());

    let _a: Vec<_> = data
        .into_par_iter()
        .map_with(sender, |s, d| s.send(scheduler(d)))
        .collect();

    let b: Vec<_> = receiver.iter().collect();
    b[0]
}

fn bench(c: &mut Criterion) {
    c.bench_function("tokio", |b| {
        let mut data: Vec<Data> = (0..10000)
            .into_par_iter()
            .map(|_| Data::new(1000, 100, 1000))
            .collect::<Vec<Data>>();

        b.iter(|| black_box(tokio_bench(&mut data)))
    });

    c.bench_function("async", |b| {
        let mut data: Vec<Data> = (0..10000)
            .into_par_iter()
            .map(|_| Data::new(1000, 100, 1000))
            .collect::<Vec<Data>>();

        b.iter(|| black_box(async_bench(&mut data)))
    });

    c.bench_function("sequential", |b| {
        let mut data: Vec<rust_scheduler::sequential::data::Data> = (0..10000)
            .into_par_iter()
            .map(|_| rust_scheduler::sequential::data::Data::new(1000, 100, 1000))
            .collect::<Vec<rust_scheduler::sequential::data::Data>>();

        b.iter(|| black_box(sequential_bench(&mut data)))
    });

    c.bench_function("speculative", |b| {
        let data: Vec<rust_scheduler::speculative::data::Data> = (0..10000)
            .into_par_iter()
            .map(|_| rust_scheduler::speculative::data::Data::new(1000, 100, 1000))
            .collect::<Vec<rust_scheduler::speculative::data::Data>>();

        let arc = Arc::new(RwLock::new(data));

        b.iter(|| black_box(speculative_bench(arc.clone())))
    });
}

criterion_group! {
    name = benches;
    config = Criterion::default().with_profiler(PProfProfiler::new(100, Output::Flamegraph(None)));
    targets = bench
}
criterion_main!(benches);
