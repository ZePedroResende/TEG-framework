use crossbeam_channel::{Receiver, Sender};
use std::collections::{HashMap, HashSet};

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

    let mut functions: HashSet<i32> = next_functions
        .iter()
        .filter(|function| !(dependency_map(pipeline, io, **function)))
        .cloned()
        .collect();

    functions.insert(function_id);

    functions.into_iter().collect()
}

fn get_next(current_int: i32, cache: &HashMap<i32, Option<i32>>) -> i32 {
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

pub fn master(receiver: Receiver<(i32, i32)>, sender: Sender<i32>, io: bool, pipeline: usize) {
    let mut cache: HashMap<i32, Option<i32>> = HashMap::new();

    let initializer = 2;
    let mut current = 2;

    let mut no_dependency_functions = functions_no_dependencies(initializer, pipeline, io);

    no_dependency_functions.iter().for_each(|function| {
        let integer = function.clone();
        cache.insert(integer, None);
        sender.send(integer).unwrap();
    });

    loop {
        let (function_id, result) = receiver.recv().unwrap();

        cache.insert(function_id, Some(result));

        if !cache.values().any(|&val| val == None) {
            current = get_next(current, &cache);

            match current {
                0 => {
                    break;
                }
                1 => {
                    break;
                }
                _ => (),
            }

            no_dependency_functions = functions_no_dependencies(current, pipeline, io);

            no_dependency_functions.iter().for_each(|function| {
                if !cache.contains_key(function) {
                    let integer = function.clone();
                    cache.insert(integer, None);
                    sender.send(integer).unwrap();
                }
            });
        } else if current == function_id {
            current = get_next(current, &cache);
        }
    }

    drop(sender);
    drop(receiver);
}
