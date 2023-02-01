/*
 *
 * https://doc.rust-lang.org/book/ch19-06-macros.html
 *
*/

// macro_rules! say_hello {
//     () => {
//         println!("Dummy macro");
//     };
// }

// macro_rules! create_fn {
//     ($func_name: ident) => {
//         fn $func_name() {
//             println!("{:?}", stringify!($func_name));
//         }
//     };
// }

// macro_rules! print_expr {
//     ($expression: expr) => {
//         println!("{:?} = {:?}", stringify!($expression), $expression);
//     };
// }

// macro_rules! logic_expr {
//     ($left: expr ,and $right: expr) => {
//         println!(
//             "{:?} ,and {:?} = {:?}",
//             stringify!($left),
//             stringify!(right),
//             $left && $right
//         );
//     };

//     ($left: expr ,or $right: expr) => {
//         println!(
//             "{:?} ,or {:?} = {:?}",
//             stringify!($left),
//             stringify!(right),
//             $left || $right
//         );
//     };
// }

// macro_rules! find_min {
// 		($x: expr) => ($x);

// 		($x: expr, $($y: expr) ,+) => (
// 				std::cmp::min($x, find_min!($($y) ,+))
// 		)
// }

// macro_rules! calculate {
//     (eval $e: expr) => {
// 				{
// 						let val: usize = $e;
// 						println!("{} = {}", stringify!{$e}, val);
// 				}
// 		};

// 		(eval $e: expr, $(eval $es: expr) ,+) => {
// 				{
// 						calculate! { eval $e }
// 						calculate! { $(eval $es) ,+ }
// 				}
// 		}
// }

// create_fn!(foo);

// #![allow(unused)]
fn main() {
    test_vec10();

    // say_hello!();
    // foo();
    // print_expr!(1 + 2 + 3);
    // logic_expr!(1i32 + 1 == 2i32 ,and 2i32 * 2 == 4i32);
    // logic_expr!(true ,or false);

    // println!("{}", find_min!(1));
    // println!("{}", find_min!(1 + 2, 4));

    // calculate! {
    //             eval 3 + 4,
    //             eval (2 * 3) + 1,
    //     eval (1 + 2) * (12 / 4)
    // }
}

#[macro_export]
macro_rules! vec10 [
    ($($e:expr),*) => ({
        let mut _temp = ::std::vec::Vec::new();
        $(_temp.push(($e) * 10);)*
        _temp
    })
];

fn test_vec10() {
    let v10: Vec<u32> = vec10![1, 2, 3];
    println!("v10 = {:?}", v10);
}
