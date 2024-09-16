// rustup doc --core

fn main() {
    test_borrow();
    test_lifetime();
    test_rc();
    test_raw_ptr();
    test_boxed();
}

fn test_borrow() {
    let mut x = 3;
    {
        let y = &mut x;
        *y += 1; // y is immutable reference
                 // *x += 2; // x had been borrowed
    }
    x += 3;
    assert_eq!(7, x);
}

fn test_lifetime() {
    let x1 = 3;
    let mut _y1 = &x1;
    {
        let mut z1 = 4;
        _y1 = &mut z1; // z does not live long enough
                       // *_y1 += 1; // _y1 references the immutable value
    }
    // assert_eq!(3, *_y1);

    let mut x2 = 3;
    let mut _y2 = &mut x2;
    *_y2 += 1;
    assert_eq!(4, *_y2);

    let mut x3 = 3;
    let _y3 = &mut x3;
    *_y3 += 1;
    let _z3 = 4;
    // _y3 = &mut z3; // _y3 itself is immutable
    assert_eq!(4, *_y3);
}

fn test_rc() {
    use std::rc::Rc;
    let x1 = 3;
    let rc1 = Rc::new(x1);
    let rc2 = rc1.clone();
    assert_eq!(3, *rc2);
}

fn test_raw_ptr() {
    let p1: *const i32 = &3;
    unsafe {
        assert_eq!(3, *p1);
    }

    let p2: *mut i32 = &mut 3;
    unsafe {
        assert!(!p2.is_null());
        *p2 += 1;
        assert_eq!(4, *p2);
    }
}

fn test_boxed() {
    let s1: *const i32 = &1;
    let b1 = Box::new(3);
    let s2: *const i32 = &2;
    let x = *b1 + 1;
    assert_eq!(4, x);

    // b1 allocated on heap
    let p1: *const i32 = &*b1;
    println!("0x{:0x}, 0x{:0x}, 0x{:0x}", s1 as u64, s2 as u64, p1 as u64);

    let mut b2 = Box::new(3);
    *b2 += 1;
    assert_eq!(4, *b2);

    let p2: *mut i32 = Box::into_raw(b2);
    println!("0x{:0x}", p2 as u64);
}
