enum Corvid {
    Magpie,
    Raven(u32),
    Jay { color: u32, sound: u32 },
}

fn main() {
    test_match();
    test_if_let();
}

fn inspect(corvid: Corvid) {
    match corvid {
        Corvid::Magpie => println!("magpie"),
        Corvid::Raven(u) => println!("raven({})", u),
        Corvid::Jay { color, sound } => println!("jay{{color:{}, sound:{}}}", color, sound),
    }
}

fn test_match() {
    let magpie = Corvid::Magpie;
    let raven = Corvid::Raven(3);
    let jay = Corvid::Jay { color: 1, sound: 2 };

    inspect(magpie);
    inspect(raven);
    inspect(jay);
}

fn test_if_let() {
    let raven = Corvid::Raven(3);

    if let Corvid::Magpie = raven {
        println!("magpie");
    } else {
        println!("!magpie");
    }

    if let Corvid::Raven(x) = raven {
        println!("raven({})", x);
    }
}
