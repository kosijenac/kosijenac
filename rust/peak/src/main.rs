fn main() -> () {
    let v1 = vec![5, 6, -2, 5, 3, -7, 9, -12, 8, 4];
    let v2 = vec![-8, -6, -1, 0, 3, 4, 6, 7, 9];
    let v3 = vec![12, 9, 8, 6, 4, 3, 1, 0, -3, -2, -1];
    let v4 = vec!['d', 'e', '4', ' ', '.', 'y', '\\', '/', ']'];

    println!("Vrh niza {:?} je {}.\n", v1, find_peak(&v1).unwrap());
    println!("Vrh niza {:?} je {}.\n", v2, find_peak(&v2).unwrap());
    println!("Vrh niza {:?} je {}.\n", v3, find_peak(&v3).unwrap());
    println!("Vrh niza {:?} je {}.\n", v4, find_peak(&v4).unwrap());
}

fn find_peak<'a, T: Ord>(v: &'a [T]) -> Option<&'a T> {
    if v.len() == 0 {
        println!("Niz treba imati barem jedan element.\n");
        return None;
    }
    let index_mid = v.len() / 2;
    let midpoint = v.get(index_mid).unwrap();
    let greater_than_left = match index_mid {
        0 => true,
        positive => match v.get(positive - 1) {
            Some(left_neighbour) => left_neighbour <= midpoint,
            None => true,
        },
    };
    let greater_than_right = match v.get(index_mid + 1) {
        Some(right_neighbour) => right_neighbour <= midpoint,
        None => true,
    };
    if greater_than_left && greater_than_right {
        return Some(&v[index_mid]);
    }
    if !greater_than_left {
        return find_peak(&v[..index_mid]);
    }
    return find_peak(&v[index_mid + 1..]);
}
