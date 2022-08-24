#![allow(unused)]

fn main() {
    let b1 = Box::new(5);
    println!("b1 = {}", b1);

    use crate::List::{Cons, Nil};

    let l1 = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));

    println!();
    println!("ddd");
}

enum List {
    Cons(i32, Box<List>),
    Nil,
}
