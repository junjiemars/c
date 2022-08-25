#![allow(unused)]

use crate::List::{Cons, Nil};

fn main() {
    let b1 = Box::new(5);
    println!("b1 = {}", b1);

    let mut b2 = Box::new(0);
    *b2 = *b2 + 1;

    let a1 = BoxedArray {
        aa: Box::new([1, 2, 3]),
    };
    println!("a1 = {}", a1);

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
        let mut cons = &*self;
        let mut tail = String::new();
        loop {
            match cons {
                Nil => {
                    write!(f, "Nil");
                    break;
                }
                Cons(car, cdr) => {
                    write!(f, "({}, ", car);
                    tail.push(')');
                    cons = &*cdr;
                }
            }
        }
        write!(f, "{}", tail)
    }
}

struct BoxedArray<T> {
    aa: Box<[T]>,
}

impl<T: fmt::Display> fmt::Display for BoxedArray<T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "_[");
        for a in &self.aa[..] {
            write!(f, "{}", *a);
        }
        write!(f, "]_")
    }
}
