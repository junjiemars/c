/*
 * https://doc.rust-lang.org/stable/reference/variables.html
 *
 */

#![allow(unused)]
fn main() {
    let init_should_be;
    let init_may_be;

    if random_bool() {
        init_should_be = ();
        init_may_be = ();
    } else {
        init_should_be = ();
    }

    assert_eq!(init_should_be, ());

    // `E0381' use of possibly-uninitialized `init_may_be`
    // assert_eq!(init_may_be, ());
}

fn random_bool() -> bool {
    true
}
