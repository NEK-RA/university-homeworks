import math


def main(n, m, a):
    f = 0
    for c in range(1, a+1):
        for i in range(1, m+1):
            for j in range(1, n+1):
                f += math.log10(c)**7 - \
                    (abs(j)**3)/5 - 7*(31 - 62*i - (i**3)/35)
    return f

# print(main(5, 3, 4), "expected ≈ 3.87e+04")
# print(main(3, 5, 2), "expected ≈ 3.27e+04")
# print(main(6, 5, 2), "expected ≈ 6.48e+04")
# print(main(2, 5, 6), "expected ≈ 6.56e+04")
# print(main(4, 7, 4), "expected ≈ 1.72e+05") 