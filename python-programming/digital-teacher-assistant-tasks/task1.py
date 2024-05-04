# оказалось первым по популярности решением
import math


def d1ch(x, y, z):
    s1 = (((y**3) + (z**2) + z)**7) / 9
    s2 = x**3
    return s1 + s2


def d1z(x, y, z):
    s1 = ((10 - 53*x - (y**2))**4) / 13
    logexpr = (z**2) + 99 + (x**3)
    s2 = 19*math.log2(logexpr)
    return s1 + s2


def root(x, y, z):
    br = 25*(y**3) + (x**2) + 31*z
    return math.sqrt(1 + 29*(br**2))


def main(x, z, y):
    return (d1ch(x, y, z) / d1z(x, y, z)) - root(x, y, z)

# # test
# print(main(-0.99, -0.76, 0.98), "expected ≈ -5.21e+00") # ≈ -5.21e+00
# print(main(0.66, 0.39, 0.23), "expected ≈ -6.91e+01") # ≈ -6.91e+01
# print(main(-0.19, -0.74, -0.0), "expected ≈ -1.23e+02") # ≈ -1.23e+02
# print(main(0.92, -0.05, -0.13), "expected ≈ -4.21e+00") # ≈ -4.21e+00
# rint(main(-0.41, -0.51, -0.33), "expected ≈ -8.91e+01") # ≈ -8.91e+01