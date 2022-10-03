use libc::{getpid, printf, strlen};
use std::ffi::CString;

fn main() {
    // getpid
    let pid = unsafe { getpid() };
    println!("pid = {}", pid);

    // printf
    unsafe {
        let cstr = CString::new("Inside C, %d\n").expect("XX");
        printf(cstr.as_ptr(), pid);
    }

    // strlen
    unsafe {
        let cstr = CString::new("Inside C").expect("XX");
        let fmt = CString::new("strlen(\"%s\") = %d\n").expect("XX");
        let len = strlen(cstr.as_ptr());
        printf(fmt.as_ptr(), cstr.as_ptr(), len);
    }
}
