pub fn find_array_peak<'a, T: Ord>(v: &'a [T]) -> Option<&'a T> {
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
        return find_array_peak(&v[..index_mid]);
    }
    return find_array_peak(&v[index_mid + 1..]);
}
pub fn find_matrix_peak<'b, U: Ord>(m: &'b [&'b [U]]) -> Option<&'b U> {
    if m.len() == 0 {
        println!("Matrica treba imati barem jedan element.\n");
        return None;
    }
    if m.len() == 1 && m[0].len() == 1 {
        return Some(&m[0][0]);
    }
    let (max_i, max_j) = find_max_on_cross(m);
    let checks = check_if_peak(m, max_i, max_j);
    let mut first_greater = 1000;
    for i in 0..4 {
        if checks[i] == false {
            first_greater = i;
            break;
        }
    }
    let max_top = max_i < m.len() / 2;
    let max_left = max_j < m.len() / 2;
    if first_greater == 0 && max_left || first_greater == 2 && max_top {
        return find_matrix_peak(&m[..m.len() / 2][..m.len() / 2]);
    } else if first_greater == 0 && !max_left || first_greater == 3 && max_top {
        return find_matrix_peak(&m[..m.len() / 2][m.len() / 2 + 1..]);
    } else if first_greater == 1 && max_left || first_greater == 2 && !max_top {
        return find_matrix_peak(&m[m.len() / 2 + 1..][..m.len() / 2]);
    } else if first_greater == 1 && !max_left || first_greater == 3 && !max_top {
        return find_matrix_peak(&m[m.len() / 2 + 1..][m.len() / 2 + 1..]);
    }
    return Some(&m[max_i][max_j]);
}
fn find_max_on_cross<U: Ord>(m: &[&[U]]) -> (usize, usize) {
    let i_mid = m.len() / 2;
    let mut current_max = &m[i_mid][i_mid];
    let mut current_max_i = i_mid;
    let mut current_max_j = i_mid;
    for i in 0..m.len() {
        if m[i][i_mid] > *current_max {
            current_max = &m[i][i_mid];
            current_max_i = i;
            current_max_j = i_mid;
        }
        if m[i_mid][i] > *current_max {
            current_max = &m[i_mid][i];
            current_max_i = i_mid;
            current_max_j = i;
        }
    }
    return (current_max_i, current_max_j);
}
fn check_if_peak<U: Ord>(m: &[&[U]], i: usize, j: usize) -> [bool; 4] {
    let greater_than_top = match i {
        0 => true,
        positive => m[positive][j] > m[positive - 1][j],
    };
    let greater_than_bottom = match m.len() - i - 1 {
        0 => true,
        positive => m[m.len() - positive - 1][j] > m[m.len() - positive][j],
    };
    let greater_than_left = match j {
        0 => true,
        positive => m[i][positive] > m[i][positive - 1],
    };
    let greater_than_right = match m.len() - j - 1 {
        0 => true,
        positive => m[i][m.len() - positive - 1] > m[i][m.len() - positive],
    };
    return [
        greater_than_top,
        greater_than_bottom,
        greater_than_left,
        greater_than_right,
    ];
}
