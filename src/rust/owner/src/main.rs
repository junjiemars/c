fn main() {
    let s1 = String::from("abc");
    let (s11, len) = calculate_length1(s1);
    println!("len({}) = {}", s11, len);

    let s2 = String::from("def");
    let len2 = calculate_length2(&s2);
    println!("len({}) = {}", s2, len2);

    let mut s3 = String::from("123");
    let len3 = calculate_length3(&mut s3);
    println!("len({}) = {}", s3, len3);

    let mut s4 = String::from("hello world");
    let w4 = first_word1(&s4);
    println!("word(\"{}\") = {}", s4, w4);
    s4.clear();
    println!("word(\"{}\") = {}", s4, w4);

		let /* mut */ s5 = String::from("hello world");
    let w5 = first_word2(&s5);
    println!("word(\"{}\") = {}", s5, w5);
    // s5.clear();
}

fn calculate_length1(s: String) -> (String, usize) {
    let length = s.len();
    return (s, length);
}

fn calculate_length2(s: &String) -> usize {
    return s.len();
}

fn calculate_length3(s: &mut String) -> usize {
    s.push_str(",abc");
    return s.len();
}

fn first_word1(s: &String) -> usize {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }

    return s.len();
}

fn first_word2(s: &String) -> &str {
		let bytes = s.as_bytes();

		for (i, &item) in bytes.iter().enumerate() {
				if item == b' ' {
						return &s[0..i];
				}
		}

		return &s[..];
}
