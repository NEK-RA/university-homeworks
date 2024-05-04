import math


def main(z):
    if z < 131:
        return z - (z**5) - 62*(z**2)
    elif 131 <= z < 155:
        return 24*(z**6)
    elif 155 <= z < 248:
        return z**4
    elif 248 <= z < 291:
        return (math.exp(z)**2) + 41*(z**6)
    else:
        return z**6

# print(main(281), "expected ≈ 1.18e+244")
# print(main(242), "expected ≈ 3.43e+09")
# print(main(173), "expected ≈ 8.96e+08")
# print(main(155), "expected ≈ 5.77e+08") 
# print(main(302), "expected ≈ 7.59e+14")