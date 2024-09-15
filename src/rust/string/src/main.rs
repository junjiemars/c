use std::slice;
use std::str;
// mod umbra;

fn main() {
    test_str_literal();
    test_byte_string();
}

fn test_str_literal() {
    let escape1 = "|\x61\x62\u{211d}\x63|";
    println!(
        "{escape1}: len={}, chars={:?}, count={}",
        escape1.len(),
        escape1.chars(),
        escape1.chars().count()
    );
    assert_eq!(escape1.chars().count(), 6);
    let p1 = escape1.as_ptr();
    unsafe {
        let a1 = slice::from_raw_parts(p1, escape1.len());
        if let Ok(s2) = str::from_utf8(a1) {
            assert_eq!(s2, escape1);
        }
    }

    let long1 = "long long ago, \
                   there is a mountain,
and a temple on it.";
    println!("{long1}");
    let raw1 = r"|ab\u{211d}c|";
    println!("{raw1}");

    let quote1 = r#"a double quotes |"| in side"#;
    println!("{quote1}");

    let quote2 = r##"a quote |"| and sharp |#|"##;
    println!("{quote2}");
}

fn test_byte_string() {
    let b1 = b"abc";
    assert!(b1.len() == 3 && b1[0] == 0x61u8);
    println!("{:?}", b1);

    if let Ok(s1) = str::from_utf8(b1) {
        assert!(s1 == "abc" && b1 == s1.as_bytes());
    }

    let quote1 = br###"ab|"##|c"###;
    if let Ok(s2) = str::from_utf8(quote1) {
        assert!(quote1[0] == 0x61 && quote1.len() == s2.len())
    }

    let b2 = b"\xe4\xb8\xad";
    match str::from_utf8(b2) {
        Ok(s) => {
            let s1 = String::from("中");
            assert_eq!(s1, s)
        }
        Err(e) => println!("error: {:?}", e),
    }
}
