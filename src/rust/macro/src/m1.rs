#[macro_export]
macro_rules! vec10 [
		($($e:expr),*) => {
				let mut _tmp = ::std::vec::Vec::new();
				$(_tmp.push($(e) * 10))*
				_tmp
		}
];
