//
// https://github.com/rust-lang/rfcs/blob/master/text/1291-promote-libc.md
//

fn main() {
    let pid = getpid();
    println!("getpid() = {pid}");

    let ss = "Inside C";
    let ss_len = strlen(ss);
    println!("strlen({ss}) = {ss_len} ");

    test_printf("printf(\"%s\")\n", ss);
}

fn getpid() -> i32 {
    use libc::getpid;
    // getpid(2)
    let pid = unsafe { getpid() };
    return pid;
}

fn strlen(ss: &str) -> usize {
    use libc::strlen;
    use std::ffi::CString;
    // strlen(3)
    let len = match CString::new(ss) {
        Ok(cstr) => unsafe { strlen(cstr.as_ptr()) },
        Err(_) => 0,
    };
    return len;
}

fn test_printf(fmt: &str, ss: &str) -> i32 {
    use libc::printf;
    use std::ffi::CString;
    if let Ok(fmt) = CString::new(fmt) {
        if let Ok(ss) = CString::new(ss) {
            // printf(3)
            unsafe {
                let _ = printf(fmt.as_ptr(), ss.as_ptr());
            }
        }
    }
    return 0;
}
