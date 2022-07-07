use minigrep::Config;
use std::{env, process};

fn main() {
    let args: Vec<String> = env::args().collect();
    let config = Config::new(&args).unwrap_or_else(|e| {
        println!("Problem parsing args: {}", e);
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {}", config.file);

    if let Err(e) = minigrep::run(config) {
        println!("Critical error: {}", e);
        process::exit(2);
    }
}
