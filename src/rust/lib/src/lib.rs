#![allow(unused)]

mod customer {
    use crate::front_of_house::hosting;

    pub fn eat_at_restaurant() {
        // front_of_house::hosting::add_to_waitlist();
        hosting::add_to_waitlist();

        let mut meal = crate::back_of_house::Breakfast::summer("Rye");
        meal.toast = String::from("Wheat");
        println!("I'd like {} toast please", meal.toast);

        // meal.seasonal_fruit = String::from("blueberries");

        let order1 = crate::back_of_house::Appetizer::Soup;
        let order2 = crate::back_of_house::Appetizer::Salad;
    }
}

mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}

        fn seat_at_table() {}
    }

    mod serving {
        fn take_order() {}

        fn serve_order() {}

        fn take_payment() {}
    }
}

mod back_of_house {

    fn fix_incorrect_order() {
        cook_order();
        super::deliver_order();
    }

    fn cook_order() {}

    pub struct Breakfast {
        pub toast: String,
        seasonal_fruit: String,
    }

    pub enum Appetizer {
        Soup,
        Salad,
    }

    impl Breakfast {
        pub fn summer(toast: &str) -> Breakfast {
            Breakfast {
                toast: String::from(toast),
                seasonal_fruit: String::from("peaches"),
            }
        }
    }
}

fn deliver_order() {}

use std::fmt;
use std::io;

fn fn1() -> fmt::Result {
		Ok(())
}

fn fn2() -> io::Result<()> {
		Ok(())
}

use std::io::Result as IoResult;

fn fn3() -> IoResult<()> {
		Ok(())
}
