use std::{error::Error, fs};

pub struct Config {
    pub query: String,
    pub file: String,
}
impl Config {
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() != 3 {
            return Err("expected 2 arguments");
        }
        let query = args[1].clone();
        let file = args[2].clone();
        Ok(Config { query, file })
    }
}
pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file)?;

    println!("Text in file:\n{}", contents);

    Ok(())
}
