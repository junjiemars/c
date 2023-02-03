/*
 * https://doc.rust-lang.org/stable/reference/type-system.html
 */

pub(crate) fn test() {
    tp_never();
}

fn tp_never() {
    #![allow(unused)]
    fn never() -> ! {
        panic!("(no return)")
    }
    // never();
}
