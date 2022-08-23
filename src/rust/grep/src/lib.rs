#![allow(unused)]

use std::error::Error;
use std::fs;

pub fn run(c: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(c.file_path)?;
		
		for line in search(&c.query, &contents) {
				println!("{line}");
		}
    Ok(())
}

pub struct Config {
    pub query: String,
    pub file_path: String,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }
        Ok(Config {
            query: args[1].clone(),
            file_path: args[2].clone(),
        })
    }
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
		let mut results = Vec::new();
		
		for line in contents.lines() {
				if (line.contains(query)) {
						results.push(line);
				}
		}
		results
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";
        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}
