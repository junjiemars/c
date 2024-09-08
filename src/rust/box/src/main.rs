//
// https://doc.rust-lang.org/std/boxed/struct.Box.html
//

#![allow(unused)]

use crate::List::{Cons, Nil};
use std::fmt;
use std::ops;

fn main() {
    boxing();
    deref_ct_cu();
    deref_mt_mu();
    deref_mt_u();
    drop0();
}

fn boxing() {
    let b1 = Box::new(5);
    println!("b1 = {}", b1);

    let mut b2 = Box::new(0);
    *b2 = *b1 + 1;
    println!("b2 = {b2}");

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

fn deref_ct_cu() {
    let b1 = 5;
    let b2 = Box::new(b1);
    assert_eq!(b1, *b2);

    let b3 = DerefOnBox::new(b1);
    assert_eq!(b1, *b3);
}

fn deref_mt_mu() {
    let mut b1 = 5;

    let mut b2 = DerefOnBox::new(&mut b1);
    assert_eq!(5, **b2);
}

fn deref_mt_u() {
    let mut b1 = 5;

    let b2 = DerefOnBox::new(&b1);
    assert_eq!(5, **b2);
}

fn drop0() {
    let s1 = String::from("A");
    let s2 = Ptr1 {
        data: String::from("B"),
    };
    drop1(s2);
}

fn drop1(s: Ptr1) {
    drop2(s);
}

fn drop2(s: Ptr1) {
    let p1 = Ptr1 {
        data: String::from("C"),
    };
    let p2 = Ptr1 {
        data: String::from("D"),
    };
    drop(s);
}

enum List {
    Cons(i32, Box<List>),
    Nil,
}

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

struct DerefOnBox<T>(T);

impl<T> DerefOnBox<T> {
    fn new(x: T) -> DerefOnBox<T> {
        DerefOnBox(x)
    }
}

impl<T> ops::Deref for DerefOnBox<T> {
    type Target = T;

    fn deref(&self) -> &T /* &Self::Target */ {
        &self.0
    }
}

impl<T> ops::DerefMut for DerefOnBox<T> {
    fn deref_mut(&mut self) -> &mut T {
        &mut self.0
    }
}

struct Ptr1 {
    data: String,
}

impl Drop for Ptr1 {
    fn drop(&mut self) {
        println!("dropping {}@{:p}", self.data, &self.data);
    }
}
