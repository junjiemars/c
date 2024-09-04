use clap::Parser;
use rusty_tesseract;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Args {
    /// source
    #[arg(short, long)]
    source: String,

    /// dest
    #[arg(short, long, default_value = "spec.json")]
    dest: Option<String>,
}

fn main() {
    println!("Hello, world!");
}

mod tests {
    use rusty_tesseract;
    #[test]
    fn test_list_lang() {
        get_tesseract_langs();
    }
		#[test]
		fn test_list_parameters() {
				get_tesseract_config_parameters();
		}
}
