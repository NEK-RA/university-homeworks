# Единственный способ? пометок про популярность решения нет
def f_big(Xs: set):
    f_set = set()
    for x in Xs:
        if (x > -71) or (x <= 95):
            f_set.add(x**3 + 3*x)
    return f_set


def k_big(Xs: set, Fs: set):
    k_set = set()
    for x in Xs:
        for f in Fs:
            if x >= f:
                k_set.add(x*f)
    return k_set


def i_big(Fs: set):
    i_set = set()
    for f in Fs:
        if not (f > -4 and f <= 39):
            i_set.add(f//4)
    return i_set


def nu(Ks: set, Is: set):
    nu = len(Ks)
    isum = 0
    for i in Is:
        isum += i % 3
    nu += isum
    return nu


def main(Xs: set):
    Fs = f_big(Xs)
    Ks = k_big(Xs, Fs)
    Is = i_big(Fs)
    return nu(Ks, Is)

# test
# X_SET_1 = {1, 4, 5, 43, 15, -76, -10, 25, 92, -35}
# X_SET_2 = {4, 38, 9, -19, 78, -49, 17, 50, 84}
# print(main(X_SET_1), "= 47")
# print(main(X_SET_2), "= 28")
