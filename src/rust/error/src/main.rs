#![allow(unused)]

use std::fs::{self, File};
use std::io::ErrorKind;
use std::io::{self, Read};

fn main() {
    // panic!("Yeah,");

    // let v = vec![1,2,3,];
    // v[10];

    let fname = "out/tmp/x1.txt";

    // let greeting_file = File::open(fname).unwrap();

    // let greeting_file = File::open(fname).expect("x1.txt should be in path");

    let greeting_file1 = match File::open(fname) {
        Ok(f1) => f1,
        Err(err1) => match err1.kind() {
            ErrorKind::NotFound => match File::create(fname) {
                Ok(f2) => f2,
                Err(err2) => panic!("{:?}", err2),
            },
            other_err => panic!("{:?}", other_err),
        },
    };

    let greeting_file2 = File::open(fname).unwrap_or_else(|err1| {
        if err1.kind() == ErrorKind::NotFound {
            File::create(fname).unwrap_or_else(|err2| {
                panic!("{:?}", err2);
            })
        } else {
            panic!("{:?}", err1);
        }
    });

    let makefile = "Makefile";

    let m1 = match read_file1(makefile) {
        Ok(c) => c,
        Err(e) => panic!("{:?}", e),
    };
    println!("{}", m1);

    let m2 = match read_file2(makefile) {
        Ok(c) => c,
        Err(e) => panic!("{:?}", e),
    };
    println!("{}", m2);

    let m3 = match read_file3(makefile) {
        Ok(c) => c,
        Err(e) => panic!("{:?}", e),
    };
    println!("{}", m3);

    assert_eq!(None, last_char_of_first_line(""));
    assert_eq!(Some('c'), last_char_of_first_line("abc\ndef"));
}

fn read_file1(name: &str) -> Result<String, io::Error> {
    let mut file = match File::open(name) {
        Ok(f) => f,
        Err(e) => return Err(e),
    };

    let mut cont = String::new();

    match file.read_to_string(&mut cont) {
        Ok(_) => Ok(cont),
        Err(e) => Err(e),
    }
}

fn read_file2(name: &str) -> Result<String, io::Error> {
    let mut cont = String::new();
    File::open(name)?.read_to_string(&mut cont)?;
    Ok(cont)
}

fn read_file3(name: &str) -> Result<String, io::Error> {
    fs::read_to_string(name)
}

fn last_char_of_first_line(s: &str) -> Option<char> {
    s.lines().next()?.chars().last()
}
