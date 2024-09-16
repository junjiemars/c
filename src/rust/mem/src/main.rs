// https://doc.rust-lang.org/reference/type-layout.html

fn main() {
    mem_alloc::test_alloc();
    mem_type_layout::size_and_align();
}

mod mem_alloc {
    use std::alloc::{GlobalAlloc, Layout};
    use std::cell::UnsafeCell;
    use std::ptr::null_mut;
    use std::sync::atomic::{AtomicUsize, Ordering::Relaxed};

    const ARENA_SIZE: usize = 128 * 1024;
    const MAX_SUPPORTED_ALIGN: usize = 4096;
    #[repr(C, align(4096))] // 4096 == MAX_SUPPORTED_ALIGN
    struct SimpleAllocator {
        arena: UnsafeCell<[u8; ARENA_SIZE]>,
        remaining: AtomicUsize, // we allocate from the top, counting down
    }

    #[global_allocator]
    static ALLOCATOR: SimpleAllocator = SimpleAllocator {
        arena: UnsafeCell::new([0x55; ARENA_SIZE]),
        remaining: AtomicUsize::new(ARENA_SIZE),
    };

    unsafe impl Sync for SimpleAllocator {}

    unsafe impl GlobalAlloc for SimpleAllocator {
        unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
            let size = layout.size();
            let align = layout.align();

            // `Layout` contract forbids making a `Layout` with align=0, or align not power of 2.
            // So we can safely use a mask to ensure alignment without worrying about UB.
            let align_mask_to_round_down = !(align - 1);

            if align > MAX_SUPPORTED_ALIGN {
                return null_mut();
            }

            let mut allocated = 0;
            if self
                .remaining
                .fetch_update(Relaxed, Relaxed, |mut remaining| {
                    if size > remaining {
                        return None;
                    }
                    remaining -= size;
                    remaining &= align_mask_to_round_down;
                    allocated = remaining;
                    Some(remaining)
                })
                .is_err()
            {
                return null_mut();
            };
            self.arena.get().cast::<u8>().add(allocated)
        }
        unsafe fn dealloc(&self, _ptr: *mut u8, _layout: Layout) {}
    }

    pub fn test_alloc() {
        let _s = format!("allocating a string!");
        let currently = ALLOCATOR.remaining.load(Relaxed);
        println!("allocated so far: {}", ARENA_SIZE - currently);
    }
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
