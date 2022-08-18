use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {
    println!("Guess the number!");

    let secret_number = rand::thread_rng().gen_range(1..=100);

    // println!("The secret number is: {secret_number}");

    loop {
        println!("Please input your guess [1,100].");

        let mut line = String::new();

        io::stdin()
            .read_line(&mut line)
            .expect("Failed to read line");

        println!("You guessed: {line}");

        match line.trim().cmp("Q") {
            Ordering::Equal => {
                println!("Quit");
                break;
            }
            _ => {
                let guess: u32 = match line.trim().parse() {
                    Ok(num) => num,
                    Err(_) => continue,
                };

                match guess.cmp(&secret_number) {
                    Ordering::Less => println!("Too small!"),
                    Ordering::Greater => println!("Too big!"),
                    Ordering::Equal => {
                        println!("Yor win!");
                        break;
                    }
                }
            }
        }
    }
}
