// https://doc.rust-lang.org/reference/type-layout.html

fn main() {
    mem_type_layout::size_and_align();
}

mod mem_type_layout {
    use std::mem::{align_of_val, size_of};

    pub fn size_and_align() {
        let i = 123;
        let l = 123i64;
        assert_eq!(size_of::<i32>(), align_of_val(&i));
        assert_eq!(size_of::<i64>(), align_of_val(&l));
    }
}
