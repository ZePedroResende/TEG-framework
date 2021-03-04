use crate::parallel_speculative::utils::{DEPENDENCY_MAP, FLOW_MAP};
use crossbeam_channel::{Receiver, Sender};
use std::collections::{HashMap, HashSet};

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

pub fn master(receiver: Receiver<(i32, i32)>, sender: Sender<i32>, improved: bool) {
    let mut cache: HashMap<i32, Option<i32>> = HashMap::new();

    let initializer = 2;
    let mut current = 2;

    let mut no_dependency_functions = functions_no_dependencies(initializer);

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

            no_dependency_functions = functions_no_dependencies(current);

            no_dependency_functions.iter().for_each(|function| {
                if !cache.contains_key(function) {
                    let integer = function.clone();
                    cache.insert(integer, None);
                    sender.send(integer).unwrap();
                }
            });
        } else if improved && current == function_id {
            current = get_next(current, &cache);
        }
    }

    drop(sender);
    drop(receiver);
}
