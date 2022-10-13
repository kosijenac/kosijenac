import numpy as np

m1 = np.array([
    [2, 5, 17, 19, 14],
    [13, 15, 8, 16, 1],
    [3, -2, 0, 11, 10],
    [-8, 4, 6, 12, -3],
    [-7, -3, -1, 7, 5]])
m2 = np.array([
    [0, 3, 4, 6, 7, 9],
    [-2, 5, 3, -7, 9, -12],
    [3, 1, 0, -3, -2, -1],
    [5, 6, -2, 5, 3, -7],
    [-8, -6, -1, 0, 3, 4],
    [9, 8, 6, 4, 3, 1]])
m3 = np.array([
    [4, 10, 1, 3],
    [6, 11, 5, 7],
    [2, 9, 8, 12],
    [0, 1, 4, 13]])


def find_peak(m):
    if len(m) == 0:
        print("Matrica treba imati barem jedan element.\n")
        return None
    if len(m) == 1 and len(m[0]) == 1:
        return m[0][0]
    max_i, max_j = find_max_on_cross(m)
    checks = check_if_peak(m, max_i, max_j)
    first_greater = -1
    for i in range(4):
        if checks[i] == False:
            first_greater = i
            break
    top_half = max_i < len(m) // 2
    left_half = max_j < len(m) // 2
    if first_greater == 0 and left_half or first_greater == 2 and top_half:
        return find_peak(m[:len(m) // 2, :len(m) // 2])
    if first_greater == 0 and not left_half or first_greater == 3 and top_half:
        return find_peak(m[:len(m) // 2, len(m) // 2 + 1:])
    if first_greater == 1 and left_half or first_greater == 2 and not top_half:
        return find_peak(m[len(m) // 2 + 1:, :len(m) // 2])
    if first_greater == 1 and not left_half or first_greater == 3 and not top_half:
        return find_peak(m[len(m) // 2 + 1:, len(m) // 2 + 1:])
    return m[max_i][max_j]


def find_max_on_cross(m):
    i_mid = len(m) // 2
    current_max = m[i_mid][i_mid]
    max_i, max_j = i_mid, i_mid
    for i in range(len(m)):
        if m[i][i_mid] > current_max:
            max_i = i
            max_j = i_mid
            current_max = m[i][i_mid]
        if m[i_mid][i] > current_max:
            max_i = i_mid
            max_j = i
            current_max = m[i_mid][i]
    return [max_i, max_j]


def check_if_peak(m, i, j):
    top = True if i == 0 else m[i][j] > m[i - 1][j]
    bottom = True if i == len(m) - 1 else m[i][j] > m[i + 1][j]
    left = True if j == 0 else m[i][j] > m[i][j - 1]
    right = True if j == len(m) - 1 else m[i][j] > m[i][j + 1]
    return [top, bottom, left, right]


print(f'Vrh matrice {m1} je {find_peak(m1)}.')
print(f'Vrh matrice {m2} je {find_peak(m2)}.')
print(f'Vrh matrice {m3} je {find_peak(m3)}.')
