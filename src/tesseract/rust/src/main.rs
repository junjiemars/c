use clap::Parser;

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

}

mod tests {
    #[test]
    fn test_list_langs() {
        let langs = rusty_tesseract::get_tesseract_langs();
				println!("{:#?}", langs)
    }
		#[test]
		fn test_list_params() {
				let params = rusty_tesseract::get_tesseract_config_parameters();
				println!("{:#?}", params)
		}
}
