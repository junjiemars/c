fn main() {
    test_str_literal();
    test_byte_string();
}

fn test_str_literal() {
    let escape1 = "|\x61\x62\u{211d}\x63|";
    println!("{escape1}");

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
    use std::str;
    let b1 = b"abc";
    assert!(b1.len() == 3 && b1[0] == 0x61u8);
    println!("{:?}", b1);

    if let Ok(s1) = str::from_utf8(b1) {
        assert!(s1 == "abc");
    }

    let quote1 = br###"ab|"##|c"###;
    if let Ok(s2) = str::from_utf8(quote1) {
        assert!(quote1[0] == 0x61 && quote1.len() == s2.len())
    }

    let b2 = b"\x4e\x2d";
    match str::from_utf8(b2) {
        Ok(s) => println!("{s}"),
        Err(e) => println!("error: {:?}", e)
    }
}
