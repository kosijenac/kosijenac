fn main() {
    let fruit = vec![
        '🍎', '🍐', '🍊', '🍊', '🍎', '🍎', '🍎', '🍐', '🍐', '🍊', '🍐', '🍎', '🍎', '🍎', '🍎',
    ];
    let small: Vec<u8> = vec![
        124, 0, 13, 51, 201, 42, 13, 43, 59, 73, 13, 13, 13, 92, 102, 43, 84, 13, 13, 28, 162, 11,
    ];
    let binary = vec![true, true, false, false, false, true, true, false, true];
    let misc = vec!["🐔", "🐔", "🌈", "🐱", "🌈", "🐶", "🌈", "🐱", "🌈", "🐱"];
    println!(
        "Kandidat za vecinu niza {:?} je {}, te on {} apsolutna vecina.",
        fruit,
        find_majority(&fruit).unwrap(),
        match check_majority(&fruit, find_majority(&fruit).unwrap()) {
            true => "je",
            false => "nije",
        }
    );
    println!(
        "Kandidat za vecinu niza {:?} je {}, te on {} apsolutna vecina.",
        small,
        find_majority(&small).unwrap(),
        match check_majority(&small, find_majority(&small).unwrap()) {
            true => "je",
            false => "nije",
        }
    );
    println!(
        "Kandidat za vecinu niza {:?} je {}, te on {} apsolutna vecina.",
        binary,
        find_majority(&binary).unwrap(),
        match check_majority(&binary, find_majority(&binary).unwrap()) {
            true => "je",
            false => "nije",
        }
    );
    println!(
        "Kandidat za vecinu niza {:?} je {}, te on {} apsolutna vecina.",
        misc,
        find_majority(&misc).unwrap(),
        match check_majority(&misc, find_majority(&misc).unwrap()) {
            true => "je",
            false => "nije",
        }
    );
}
/**
 * Trazi `dominirajuci` element danog niza, tj. apsolutnu vecinu.
 * Ako je niz prazan, vraca `None`, inace vraca kandidata za vecinu.
 * Koristi https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm.
 */
fn find_majority<T: PartialEq + std::fmt::Debug>(votes: &Vec<T>) -> Option<&T> {
    let mut counter = 0;
    let mut element = match votes.get(0) {
        Some(vote) => vote,
        None => {
            println!("Niz ne smije biti prazan!");
            return None;
        }
    };
    for vote in votes.iter() {
        if counter == 0 {
            counter = 1;
            element = vote;
        } else if *element == *vote {
            counter += 1;
        } else {
            counter -= 1;
        }
        dbg!(counter);
        dbg!(element);
    }
    return Some(element);
}
/**
 * Provjerava je li dani kandidat za apsolutnu vecinu zapravo apsolutna vecina.
 * To radi tako da prebroji koliko se puta on pojavljuje u nizu.
 */
fn check_majority<T: PartialEq>(votes: &Vec<T>, candidate: &T) -> bool {
    let mut occurences = 0;
    for vote in votes.iter() {
        if *vote == *candidate {
            occurences += 1;
        }
    }
    return occurences > votes.len() / 2;
}
