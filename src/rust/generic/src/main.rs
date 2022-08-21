#![allow(unused)]
fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    assert_eq!(*largest(&number_list), 100);

    let char_list = vec!['y', 'm', 'a', 'q'];
    assert_eq!(*largest(&char_list), 'y');

    let point1 = Point { x: 1, y: 2.0 };
    assert_eq!(point1.x, *point1.x());
    assert_eq!(point1.y, *point1.y());

		let red = Color::Red(255);

    let tweet = Tweet {
        username: String::from("horse_ebook"),
        content: String::from(
            "of course, as you probably already know, \
						 people",
        ),
        reply: false,
        retweet: false,
    };
    println!("1 new tweet: {}", tweet.summarize());

    let artical = NewsArtical {
        headline: String::from("Penguins win the Stanley Cup Championship!"),
        location: String::from("Pittsburgh, PA, USA"),
        author: String::from("Iceburgh"),
        content: String::from(
            "The Pittsburgh Penguins once again are the best \
             hockey team in the NHL.",
        ),
    };
    println!("1 new artical: {}", artical.summarize());
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

pub struct Point<T, U> {
    x: T,
    y: U,
}

impl<T, U> Point<T, U> {
		fn x(&self) -> &T {
				&self.x
		}

		fn y(&self) -> &U {
				&self.y
		}
}

pub enum Color<T: std::cmp::PartialEq> {
    Red(T),
    Green(T),
    Blue(T),
    None,
}

pub trait Summary {
    fn summarize(&self) -> String;
}

pub struct NewsArtical {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for NewsArtical {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}
