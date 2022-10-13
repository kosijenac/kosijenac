import numpy as np
# koristimo numpy matrice jer one imaju najjednostavniju implementaciju horizontalnog rezanja


def find_peak(m):   # O(n)
    if len(m) == 0:
        print("Matrica treba imati barem jedan element.\n")
        return None
    # ako smo u rekurziji dosli do 1x1 matrice, tada je to sigurno vrh
    if len(m) == 1 and len(m[0]) == 1:
        return m[0][0]
    max_i, max_j = find_max_on_cross(m)
    checks = check_if_peak(m, max_i, max_j)
    first_greater = -1
    # `first_greater` nam daje prvu po redu stranu s koje se nalazi veci element od maksimuma
    for i in range(4):
        if checks[i] == False:
            first_greater = i
            break
    # ovdje zapisujemo nalazi li se maksimum u gornjoj polovici matrice, odnosno lijevoj
    top_half = max_i < len(m) // 2
    left_half = max_j < len(m[0]) // 2
    # ovisno o tome s koje je strane veci element od maksimuma, te na kojoj se polovici
    # nalazi sam maksimum, prebacujemo se na odgovarajuci kvadrant
    if first_greater == 0 and left_half or first_greater == 2 and top_half:
        return find_peak(m[:len(m) // 2, :len(m[0]) // 2])
    if first_greater == 0 and not left_half or first_greater == 3 and top_half:
        return find_peak(m[:len(m) // 2, len(m[0]) // 2 + 1:])
    if first_greater == 1 and left_half or first_greater == 2 and not top_half:
        return find_peak(m[len(m) // 2 + 1:, :len(m[0]) // 2])
    if first_greater == 1 and not left_half or first_greater == 3 and not top_half:
        return find_peak(m[len(m) // 2 + 1:, len(m[0]) // 2 + 1:])
    # ako nema veceg elementa od maksimuma, onda je upravo on vrh
    return m[max_i][max_j]


def find_max_on_cross(m):   # O(n)
    # razdijeli matricu na 4 kvadranta, te pronalazi najveci element na "krizu" koji dijeli matricu
    i_mid = len(m) // 2
    j_mid = len(m[0]) // 2
    current_max = m[i_mid][j_mid]
    max_i, max_j = i_mid, j_mid
    for i in range(len(m)):
        if m[i][j_mid] > current_max:
            max_i = i
            max_j = j_mid
            current_max = m[i][j_mid]
    for j in range(len(m[0])):
        if m[i_mid][j] > current_max:
            max_i = i_mid
            max_j = j
            current_max = m[i_mid][j]
    # vraca koordinate maksimalnog elementa
    return [max_i, max_j]


def check_if_peak(m, i, j):  # O(1)
    # za element iz matrice provjerava je li veci od svoja <= 4 susjeda te vraca bool za svaku stranu
    top = True if i == 0 else m[i][j] > m[i - 1][j]
    bottom = True if i == len(m) - 1 else m[i][j] > m[i + 1][j]
    left = True if j == 0 else m[i][j] > m[i][j - 1]
    right = True if j == len(m[0]) - 1 else m[i][j] > m[i][j + 1]
    return [top, bottom, left, right]


m1 = np.array([
    [2, 19, 17, 5, 14],
    [13, 15, 8, 16, 1],
    [3, -2, 0, 11, 10],
    [-8, 4, 6, 12, -3],
    [-7, -3, -1, 7, 5]])
m2 = np.array([
    [0, 3, 4, 6, 7, -9],
    [-2, 5, 3, -7, 8, -12],
    [3, 1, 0, -3, -2, -1],
    [5, 6, -2, 5, 3, -7],
    [-8, -6, -1, 0, 3, 4],
    [9, 8, 6, 4, 3, 1]])
m3 = np.array([
    [4, 10, 1, 3],
    [6, 11, 5, 7],
    [12, 9, 8, 1],
    [13, 4, 0, 6]])
print(f'Vrh matrice \n{m1} je {find_peak(m1)}.')
print(f'Vrh matrice \n{m2} je {find_peak(m2)}.')
print(f'Vrh matrice \n{m3} je {find_peak(m3)}.')
