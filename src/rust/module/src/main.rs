#![allow(unused)]


use crate::garden::vegetables::Asparagus;

pub mod garden;



fn main() {
		let plant = Asparagus {};
		println!("I'm growing {:?}", plant);
}

fn glob_star() {
		use std::collections::*;
}

fn nested_path() {
		use std::{fmt, io};
}
