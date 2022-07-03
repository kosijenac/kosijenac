use std::{env, fs};

fn main() {
    let args: Vec<String> = env::args().collect();
    let query = &args[1];
    let file = &args[2];
    let contents = fs::read_to_string(file).expect("Could not read file.");

    println!("Text in file:\n{}", contents);
}
