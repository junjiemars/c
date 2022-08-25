#![allow(unused)]

use crate::List::{Cons, Nil};

fn main() {
    let b1 = Box::new(5);
    println!("b1 = {}", b1);

    let l1 = Cons(
        1,
        Box::new(Cons(2, Box::new(Cons(3, Box::new(Cons(4, Box::new(Nil))))))),
    );
    println!("Cons: {}", l1);
}

enum List {
    Cons(i32, Box<List>),
    Nil,
}

use std::fmt;

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut lst = &*self;
        let mut tail = String::new();
        loop {
            match lst {
                Nil => {
                    write!(f, "Nil");
                    break;
                }
                Cons(car, cdr) => {
                    write!(f, "({}, ", car);
                    tail.push(')');
                    lst = &*cdr;
                }
            }
        }
        write!(f, "{}", tail)
    }
}
