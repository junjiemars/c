use iced::Settings;
use iced::Sandbox;

pub mod Tour;

pub fn main() -> iced::Result {
    env_logger::init();

    Tour::run(Settings::default())
}
