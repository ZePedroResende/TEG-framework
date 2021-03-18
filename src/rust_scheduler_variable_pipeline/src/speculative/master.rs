use crate::sequential::data::Data;
use crossbeam_channel::{Receiver, Sender};
use std::collections::{HashMap, HashSet};
use std::sync::{Arc, RwLock};
use std::time::SystemTime;

type Prop = for<'r> fn(&'r mut crate::sequential::data::Data) -> i32;

fn is_empty(dataset: Arc<RwLock<Vec<Data>>>) -> bool {
    loop {
        if let Ok(read_lock) = dataset.read() {
            return (*read_lock).is_empty().clone();
        }
    }
}

fn pop(dataset: Arc<RwLock<Vec<Data>>>) {
    loop {
        if let Ok(mut write_lock) = dataset.write() {
            (*write_lock).remove(0);
            break;
        }
    }
}

fn flow_map(pipeline: usize, io: bool, function_id: i32) -> Vec<i32> {
    if io {
        match pipeline {
            20 => crate::io_pipeline_20::flow_map(function_id),
            _ => crate::io_pipeline_10::flow_map(function_id),
        }
    } else {
        match pipeline {
            20 => crate::cpu_pipeline_20::flow_map(function_id),
            _ => crate::cpu_pipeline_10::flow_map(function_id),
        }
    }
}

fn dependency_map(pipeline: usize, io: bool, function: i32) -> bool {
    if io {
        match pipeline {
            20 => crate::io_pipeline_20::dependency_map(function),
            _ => crate::io_pipeline_10::dependency_map(function),
        }
    } else {
        match pipeline {
            20 => crate::cpu_pipeline_20::dependency_map(function),
            _ => crate::cpu_pipeline_10::dependency_map(function),
        }
    }
}

fn functions_no_dependencies(function_id: i32, pipeline: usize, io: bool) -> Vec<i32> {
    let next_functions: Vec<i32> = flow_map(pipeline, io, function_id);

    let functions: HashSet<i32> = next_functions
        .iter()
        .filter(|function| !(dependency_map(pipeline, io, **function)))
        .cloned()
        .collect();

    let mut flow: Vec<i32> = functions
        .iter()
        .flat_map(|f| functions_no_dependencies(*f, pipeline, io))
        .collect::<HashSet<_>>()
        .into_iter()
        .collect();

    flow.push(function_id);
    flow.into_iter().collect()
}

fn get_next(current_int: i32, cache: &HashMap<i32, Option<i32>>) -> i32 {
    /*
    let mut current = current_int;
    let mut next;

    match cache.get(&current) {
        Some(entry) => next = entry.clone(),
        None => return current,
    }

    loop {
        current = next.unwrap();
        match cache.get(&current) {
            Some(entry) => next = entry.clone(),
            None => return current,
        }
    }
    */

    loop {
        match cache.get(&current_int) {
            Some(entry) => match entry {
                Some(value) => return get_next(value.clone(), cache),
                None => return current_int,
            },
            None => return current_int,
        }
    }
}

pub fn master(
    receiver: Receiver<(i32, i32)>,
    sender: Sender<i32>,
    dataset: Arc<RwLock<Vec<Data>>>,
    io: bool,
    pipeline: usize,
) {
    let mut cache: HashMap<i32, Option<i32>> = HashMap::new();

    //    let mut now = SystemTime::now();
    let initializer = 2;
    let mut current = 2;

    let mut no_dependency_functions = functions_no_dependencies(initializer, pipeline, io);

    // let now3 = SystemTime::now();

    no_dependency_functions.iter().for_each(|function| {
        cache.insert(function.clone(), None);
        sender.send(function.clone()).unwrap();
    });

    //let c = now3.elapsed().unwrap();
    //println!("3 => {:?}", c);

    while !is_empty(dataset.clone()) {
        //let now4 = SystemTime::now();
        while cache.values().any(|&val| val == None) {
            for (function_id, result) in receiver.try_iter() {
                cache.insert(function_id, Some(result));
            }
        }
        //let c = now4.elapsed().unwrap();
        //   println!("4 => {:?}", c);

        // if !cache.values().any(|&val| val == None) {
        current = get_next(current, &cache);

        match current {
            0 => {
                //                println!("SUCESS");
                current = 2;
                pop(dataset.clone());
                cache.clear();

                //    let c = now.elapsed().unwrap();
                //       println!("{:?}", c);
                //     now = SystemTime::now();
            }
            1 => {
                //               println!("FAIL");
                current = 2;
                pop(dataset.clone());
                cache.clear();
                //      let c = now.elapsed().unwrap();
                //      println!("{:?}", c);
                //       now = SystemTime::now();
            }
            _ => (),
        }

        //let now2 = SystemTime::now();
        if !is_empty(dataset.clone()) {
            no_dependency_functions = functions_no_dependencies(current, pipeline, io);

            no_dependency_functions.iter().for_each(|function| {
                if !cache.contains_key(function) {
                    cache.insert(function.clone(), None);
                    sender.send(function.clone()).unwrap();
                }
            });
        }

        //let c = now2.elapsed().unwrap();
        //println!("2 => {:?}", c);

        //}
    }
}
