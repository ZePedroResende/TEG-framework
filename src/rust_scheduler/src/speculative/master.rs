use crate::speculative::data::Data;
use crate::speculative::utils::{DEPENDENCY_MAP, FLOW_MAP};
use crossbeam_channel::{Receiver, Sender};
use std::collections::{HashMap, HashSet};
use std::sync::{Arc, RwLock};

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

fn functions_no_dependencies(function_id: i32) -> Vec<i32> {
    let next_functions: Vec<i32> = FLOW_MAP.get(&function_id).unwrap().clone();

    let mut functions: HashSet<i32> = next_functions
        .iter()
        .filter(|function| !DEPENDENCY_MAP[&function])
        .cloned()
        .collect();

    functions.insert(function_id);

    functions.into_iter().collect()
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
    improved: bool,
) {
    let mut cache: HashMap<i32, Option<i32>> = HashMap::new();

    let initializer = 2;
    let mut current = 2;

    let mut no_dependency_functions = functions_no_dependencies(initializer);

    no_dependency_functions.iter().for_each(|function| {
        cache.insert(function.clone(), None);
        sender.send(function.clone()).unwrap();
    });

    while !is_empty(dataset.clone()) {
        let (function_id, result) = receiver.recv().unwrap();

        cache.insert(function_id, Some(result));

        if !cache.values().any(|&val| val == None) {
            current = get_next(current, &cache);

            match current {
                0 => {
                    //                println!("SUCESS");
                    current = 2;
                    pop(dataset.clone());
                    cache.clear();
                }
                1 => {
                    //               println!("FAIL");
                    current = 2;
                    pop(dataset.clone());
                    cache.clear();
                }
                _ => (),
            }

            if !is_empty(dataset.clone()) {
                no_dependency_functions = functions_no_dependencies(current);

                no_dependency_functions.iter().for_each(|function| {
                    if !cache.contains_key(function) {
                        cache.insert(function.clone(), None);
                        sender.send(function.clone()).unwrap();
                    }
                });
            }
        } else if improved {
            if current == function_id {
                current = get_next(current, &cache);
            }
        }
    }
}
