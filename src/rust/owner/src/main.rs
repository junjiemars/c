#![allow(unused)]
fn main() {
    short();

    borrow_more_than_once_at_a_time();

    combining_mutable_immutable();

    dangle1();

    lifetime1();
    lifetime2();
    lifetime3();
		lifetime4();
}

fn short() {
    let s = String::from("abc");
    println!("short: {}", s);
}

fn change(ss: &mut String) {
    ss.push_str("X");
}

fn dangle1() -> String {
    let s = String::from("A");
    // &s
    s
}

fn borrow_more_than_once_at_a_time() {
    let mut s = String::from("A");
    let s1 = &mut s;
    let s2 = &mut s;
    // println!("{}, {}", s1, s2);
    println!("{}", s2);
}

fn combining_mutable_immutable() {
    let mut s = String::from("A");
    let s1 = &s;
    let s2 = &s;
    let s3 = &mut s;
    // println!("{}, {}", s2, s3);
    println!("{}", s3);
}

fn lifetime1() {
    // let r;

    // // E0597
    // {
    // 		let x = 5;
    // 		r = &x;
    // }

    let x = 5;
    let r = &x;

    assert_eq!(*r, 5);
}

fn longest1<'a>(a: &'a str, b: &'a str) -> &'a str {
    if a.len() > b.len() {
        return a;
    } else {
        return b;
    }
}

fn lifetime2() {
    let a = "A";
    let b = "BB";
    let longest = longest1(a, b);
    assert_eq!(longest, b);
}

fn lifetime_static1() -> &'static str {
    let s: &'static str = "elder, partiarch";
    s
}

fn lifetime3() {
    let s = lifetime_static1();
    println!("{}", s);
}

pub struct Twin<'a> {
    age: &'a i32,
}

impl<'a> Twin<'a> {
    fn return_age(&self) -> &i32 {
        return self.age;
    }
}

pub struct Twin1<'a> {
    first_name: &'a str,
}

fn lifetime4() {
		let t1 = Twin { age: &22 };
		assert_eq!(*t1.age, 22);
}

fn lifetime5() {
		let t1 = Twin1 { first_name: "A" };
		assert_eq!(t1.first_name, "A");
}

