// rustup doc --core

mod core_alloc;
mod core_cell;
mod core_lifetime;
mod core_marker;
mod core_ptr;

fn main() {
    core_alloc::test_alloc();
    core_cell::test_cell();
    core_lifetime::test_lifetime();
    core_ptr::test_ptr();
    core_marker::test_marker();
}
