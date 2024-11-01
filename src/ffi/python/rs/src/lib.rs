use pyo3::prelude::*;
use std::ffi::CString;

/// Call system(3)
#[pyfunction]
fn system(command: String) -> PyResult<i32> {
    let cmd = CString::new(command)?;
    unsafe {
        let rc = libc::system(cmd.as_ptr());
        Ok(rc)
    }
}

/// Multiply two integers.
#[pyfunction]
fn multiply(a: i64, b: i64) -> PyResult<i64> {
    Ok(a * b)
}

/// A Python module implemented in Rust.
#[pymodule]
fn nore_rs(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(system, m)?)?;
    m.add_function(wrap_pyfunction!(multiply, m)?)?;
    Ok(())
}
