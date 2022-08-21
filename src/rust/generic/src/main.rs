fn main() {
		let number_list = vec![34, 50, 25, 100, 65];
		assert_eq!(*largest(&number_list), 100);

		let char_list = vec!['y', 'm', 'a', 'q'];
		assert_eq!(*largest(&char_list), 'y');
}

fn largest<T: std::cmp::PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}
