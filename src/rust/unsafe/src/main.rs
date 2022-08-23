use std::slice;

fn main() {
    let raw_ptr1: *const u32 = &10;
    unsafe {
        assert!(*raw_ptr1 == 10);
    }

    let vec1 = vec![1, 2, 3];
    let v_ptr1 = vec1.as_ptr();
    let v_len1 = vec1.len();
    unsafe {
        let v_slice1: &[u32] = slice::from_raw_parts(v_ptr1, v_len1);
        assert_eq!(vec1.as_slice(), v_slice1);
    }
}
