pub fn test_lifetime() {
    test_alias();
    test_borrow();
    test_mut();
}

fn test_alias() {
    //! - having several immutable references (`&T`) to the object
    //! (also known as **aliasing**).
    let a1 = 3;
    let r1 = &a1;
    let r2 = &a1;
    assert!(a1 == *r1 && r1 == r2);
}

fn test_borrow() {
    //! - having one mutable reference (`&mut T`) to the object
    //! (also known as **mutability**).
    let mut x = 3;
    {
        let y = &mut x;
        *y += 1; // y is immutable reference
                 // *x += 2; // x had been borrowed
    }
    x += 3;
    assert_eq!(7, x);
}

fn test_mut() {
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
