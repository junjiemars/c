fn main() {
    test_null_pointer();
    test_raw_pointer();
    test_box_pointer();
    test_addr_of();
    // let raw_ptr1: *const u32 = &10;
    // unsafe {
    //     assert!(*raw_ptr1 == 10);
    // }

    // let vec1 = vec![1, 2, 3];
    // let v_ptr1 = vec1.as_ptr();
    // let v_len1 = vec1.len();
    // unsafe {
    //     let v_slice1: &[u32] = slice::from_raw_parts(v_ptr1, v_len1);
    //     assert_eq!(vec1.as_slice(), v_slice1);
    // }
}

fn test_null_pointer() {
    let p1: *const i32 = std::ptr::null();
    assert!(p1.is_null());
    assert!(p1 as usize == 0);
    let p2: *mut i32 = std::ptr::null_mut();
    assert!(p2.is_null());
    assert!(p2 as usize == 0);
    let a1 = [1, 2, 3];
    let p3 = a1.as_ptr();
    assert!(!p3.is_null());
}

fn test_raw_pointer() {
    let v1 = 10;
    let r1: *const i32 = &v1;
    unsafe {
        assert!(*r1 == 10);
    }

    let mut v2 = 0x11223344;
    let r2: *mut i32 = &mut v2;
    unsafe {
        *r2 = *r1 + 1;
        assert!(*r2 == 11)
    }

    use std::slice;
    let vec1 = vec![1, 2, 3];
    let v_ptr1 = vec1.as_ptr();
    let v_len1 = vec1.len();
    unsafe {
        let v_slice1: &[u32] = slice::from_raw_parts(v_ptr1, v_len1);
        assert_eq!(vec1.as_slice(), v_slice1);
    }
}

fn test_box_pointer() {
    let b1 = Box::new(10);
    let r1: *const i32 = &*b1;
    unsafe { assert!(*r1 == 10) }

    let mut b2 = Box::new(0x11223344);
    let r2: *mut i32 = &mut *b2;
    unsafe {
        *r2 = *r1 + 1;
        assert!(*r2 == 11);
    }

    let r3: *mut i32 = Box::into_raw(b2);
    unsafe {
        assert!(*r3 == 11);
        drop(Box::from_raw(r3))
    }
}

#[derive(Debug, Default, Copy, Clone)]
#[repr(C, packed)]
struct S {
    aligned: u8,
    unaligned: u32,
}

fn test_addr_of() {
    let s = S::default();
    let r1 = std::ptr::addr_of!(s);
    unsafe {
        assert!(s.aligned == (*r1).aligned);
    }
    let r2 = std::ptr::addr_of!(s.unaligned);
    assert!((r1 as u64 + 1) == r2 as u64);
    unsafe {
        // should be failed:
        // assert!(s.unaligned == *r2);
        assert!(s.unaligned == r2.read_unaligned());
    }
}
