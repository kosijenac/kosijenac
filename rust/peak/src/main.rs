fn main() -> () {
    println!("Hello, world!");
}

fn find_peak_recursive<T: Ord + Copy>(v: &[T]) -> T {
    let index = v.len() / 2;
    if v[index] >= v[index - 1] && v[index] >= v[index + 1] {
        return v[index];
    }
    if v[index] < v[index - 1] {
        return find_peak_recursive(&v[..index]);
    }
    return find_peak_recursive(&v[index + 1..]);
}

fn find_peak_iterative<T: Ord + Copy>(v: &[T]) -> T {
    let mut index = v.len() / 2;
    loop {
        if v[index] >= v[index - 1] && v[index] >= v[index + 1] {
            return v[index];
        } else if v[index] < v[index - 1] {
            index /= 2;
        } else {
            index
        }
    }
}
