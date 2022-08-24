#![allow(unused)]

fn main() {
    let b1 = Box::new(5);
    println!("b1 = {}", b1);

    use crate::List::{Cons, Nil};

    let l1 = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
    println!("Cons: {}", l1);
}

enum List {
    Cons(i32, Box<List>),
    Nil,
}

use std::fmt;

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
				write!(f, "XXX")
    }
}
