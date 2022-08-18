use std::ffi::CString;

extern {
    static stdout: *mut libc::FILE;
}


fn main() {
    // getpid
    let pid = unsafe { libc::getpid() };
    println!("pid = {}", pid);
		
		// fprintf
		let cstr = CString::new("inside C, %d\n").expect("CString::new failed");
		unsafe { libc::fprintf(stdout, cstr.as_ptr(), pid); };
}
