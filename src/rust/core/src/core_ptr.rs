use core::mem::size_of;
use core::ptr;

pub fn test_ptr() {
    test_raw_ptr();
    test_boxed();
    test_rc();
}

#[allow(unused_mut)]
fn test_raw_ptr() {
    // *const T or *mut T
    let n1 = ptr::null::<i32>();
    assert!(n1.is_null() && n1 as usize == 0);
    let mut n2 = ptr::null_mut::<i32>();
    assert!(n2.is_null() && n2 as usize == 0);

    // pointer has same size
    assert_eq!(size_of::<*const u8>(), size_of::<*mut i32>());
    // usize and isize has pointer size
    assert!(
        size_of::<isize>() == size_of::<usize>()
            && size_of::<usize>() == size_of::<&u8>()
            && size_of::<&u8>() == size_of::<*const i32>()
    );

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

    let r1 = &3;
    let p3 = ptr::from_ref(r1);
    unsafe {
        assert_eq!(*r1, *p3);
    }

    let a1 = [1, 2, 3];
    let a1_ptr = a1.as_ptr();
    let a1_slice = ptr::slice_from_raw_parts(a1_ptr, a1.len());
    unsafe {
        assert_eq!((*a1_slice)[0], 1);
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

fn test_rc() {
    use std::rc::Rc;
    let x1 = 3;
    let rc1 = Rc::new(x1);
    let rc2 = rc1.clone();
    assert_eq!(3, *rc2);
}
