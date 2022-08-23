#![allow(unused)]
fn main() {
    short();

    let s1 = String::from("abc");
    let (s11, len) = calculate_length1(s1);
    println!("len({}) = {}", s11, len);

    let s2 = String::from("def");
    let len2 = calculate_length2(&s2);
    println!("len({}) = {}", s2, len2);

    let mut s3 = String::from("123");
    let len3 = calculate_length3(&mut s3);
    println!("len({}) = {}", s3, len3);

    let mut s4 = String::from("hello world");
    let w4 = first_word1(&s4);
    println!("word(\"{}\") = {}", s4, w4);
    s4.clear();
    println!("word(\"{}\") = {}", s4, w4);

    let /* mut */ s5 = String::from("hello world");
    let w5 = first_word2(&s5);
    println!("word(\"{}\") = {}", s5, w5);
    // s5.clear();

    let l1 = String::from("abcd");
    let l11 = "xyz";
    let l111 = longest1(l1.as_str(), l11);
    println!("longest1({}, {}) = {}", l1, l11, l111);

    let l21 = String::from("long long string");
    let result;
    {
        let l211 = String::from("abc");
        result = longest1(l21.as_str(), l211.as_str());
        println!("longest1 = {}", result);
    }
    // println!("longest1 = {}", result);
    let l3 = 29;
    let l31 = Twin { age: &l3 };
    assert_eq!(29, *l31.age);
    assert_eq!(29, *l31.return_age());

    let l4 = String::from("Julius");
    let l41 = Twin1 {
        first_name: l4.as_str(),
    };
    println!("twin1.first_name = {}", l41.first_name);

    let l5 = lifetime2();
    println!("static lifetime: {}", l5);

    let l6 = lifetime3();
    println!("ownership move: {}", l6);

    let m1 = String::from("abcd");
    let m11 = "abc";
    let m1r = longest_with_announcement(m1.as_str(), m11, "who care");
    println!("longest_with_announcement: {}", m1r);
}

fn short() {
    let s = String::from("abc");
    println!("short: {}", s);
}

fn calculate_length1(s: String) -> (String, usize) {
    let length = s.len();
    return (s, length);
}

fn calculate_length2(s: &String) -> usize {
    return s.len();
}

fn calculate_length3(s: &mut String) -> usize {
    s.push_str(",abc");
    return s.len();
}

fn first_word1(s: &String) -> usize {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }

    return s.len();
}

fn first_word2(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    return &s[..];
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

fn lifetime2() -> &'static str {
    let s: &'static str = "elder, partiarch";
    return s;
}

fn lifetime3() -> String {
    let s = String::from("MiIlroy");
    return s;
}

use std::fmt::Display;
fn longest_with_announcement<'a, T>(a: &'a str, b: &'a str, ann: T) -> &'a str
where
    T: Display,
{
    println!("ann: {}", ann);
    if a.len() > b.len() {
        return a;
    } else {
        return b;
    }
}
