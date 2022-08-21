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
