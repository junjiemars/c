// shareable mutable containers
use core::cell::Cell;

pub fn test_cell() {
    test_wild();
}

struct A {
    f1: u8,
    f2: Cell<i32>,
}

fn test_wild() {
    let c1 = Cell::new(3);
    assert_eq!(3, c1.get());
    let r1 = c1.replace(c1.get() + 1);
    assert!(r1 == 3 && c1.get() == 4);
    c1.set(c1.get() + 1);
    assert_eq!(5, c1.get());

    let a1 = A {
        f1: 1,
        f2: Cell::new(2),
    };
    a1.f2.set(a1.f2.get() + 1);
    assert!(a1.f1 == 1 && a1.f2.get() == 3);
}
