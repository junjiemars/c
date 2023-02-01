/*
 * https://doc.rust-lang.org/reference/attributes.html#built-in-attributes-index
 */

#[cfg(target_os = "linux")]
mod linux1;

#[cfg(target_os = "macos")]
mod macos1;

#[cfg_attr(target_os = "linux", path = "linux1.rs")]
#[cfg_attr(target_os = "macos", path = "macos1.rs")]
#[cfg_attr(target_os = "windows", path = "windows1.rs")]
mod os1;

fn main() {
    say();
}

fn say() {
    #[cfg(target_os = "linux")]
    {
        linux1::say();
    }

    #[cfg(target_os = "macos")]
    {
        macos1::say();
    }

    #[cfg(all(unix, target_pointer_width = "64"))]
    {
        println!("unix 64");
    }

    #[cfg(not(any(target_os = "linux", target_os = "macos")))]
    {
        println!("(unknown)");
    }

    os1::say();
}
