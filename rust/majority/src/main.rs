fn main() {
    println!("Hello, world!");
}
fn find_majority<T: PartialEq>(votes: &Vec<T>) -> &T {
    return &votes[0];
}
fn check_majority<T: PartialEq>(votes: &Vec<T>, candidate: &T) -> bool {
    let mut occurences = 0;
    for vote in votes.iter() {
        if *vote == *candidate {
            occurences += 1;
        }
    }
    return occurences > votes.len() / 2;
}
