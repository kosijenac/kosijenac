use peak::{find_array_peak, find_matrix_peak};

fn main() -> () {
    let v1 = vec![5, 6, -2, 5, 3, -7, 9, -12, 8, 4];
    let v2 = vec![-8, -6, -1, 0, 3, 4, 6, 7, 9];
    let v3 = vec![12, 9, 8, 6, 4, 3, 1, 0, -3, -2, -1];
    let v4 = vec!['d', 'e', '4', ' ', '.', 'y', '\\', '/', ']'];

    println!("Vrh niza {:?} je {}.\n", v1, find_array_peak(&v1).unwrap());
    println!("Vrh niza {:?} je {}.\n", v2, find_array_peak(&v2).unwrap());
    println!("Vrh niza {:?} je {}.\n", v3, find_array_peak(&v3).unwrap());
    println!("Vrh niza {:?} je {}.\n", v4, find_array_peak(&v4).unwrap());

    let m1 = &vec![&v1[..5], &v2[..5], &v3[..5], &v1[5..], &v3[5..10]];
    let m2 = &vec![&v1[2..6], &v2[2..6], &v3[2..6], &v3[6..10]];
    let m3 = &vec![&v2[3..], &v1[2..8], &v3[5..], &v1[..6], &v2[..6], &v3[1..7]];
    let m4 = &vec![&v4[..3], &v4[3..6], &v4[6..]];

    println!("Vrh mat. {:?} je {}.\n", m1, find_matrix_peak(m1).unwrap());
    println!("Vrh mat. {:?} je {}.\n", m2, find_matrix_peak(m2).unwrap());
    println!("Vrh mat. {:?} je {}.\n", m3, find_matrix_peak(m3).unwrap());
    println!("Vrh mat. {:?} je {}.\n", m4, find_matrix_peak(m4).unwrap());
}
