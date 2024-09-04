use clap::{ArgAction, Parser};

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Argv {
    /// source
    #[arg(short, long)]
    source: Option<String>,

    /// dest
    #[arg(short, long)]
    dest: Option<String>,

    /// list languages
    #[arg(long, action = ArgAction::SetTrue)]
    list_languages: bool,

    /// list parameters
    #[arg(long, action = ArgAction::SetTrue)]
    list_parameters: bool,
}

fn main() {
    // parsing args
    let argv = Argv::parse();
    if argv.list_languages {
        if let Ok(langs) = rusty_tesseract::get_tesseract_langs() {
            for lang in langs.into_iter() {
                println!("{lang}")
            }
        }
        return;
    }
    if argv.list_parameters {
        if let Ok(config) = rusty_tesseract::get_tesseract_config_parameters() {
						for param in config.config_parameters.into_iter() {
								println!("{}", param)
						}
        }
        return;
    }
}

mod tests {
    #[test]
    fn test_list_langs() {
        let langs = rusty_tesseract::get_tesseract_langs();
        println!("{langs:#?}")
    }
    #[test]
    fn test_list_params() {
        let params = rusty_tesseract::get_tesseract_config_parameters();
        println!("{params:#?}")
    }
}
