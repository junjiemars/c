pub mod tour;

pub fn main() -> iced::Result {
    env_logger::init();

    tour::run()
}
