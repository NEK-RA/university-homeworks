import pytest


class MealyError(Exception):
    def __init__(self, method):
        self.message = method
        super().__init__(self.message)

    def __str__(self):
        return self.message


class Mealy:
    def __init__(self, state="A"):
        self.state = state

    def fill(self):
        match self.state:
            case "A":
                self.state = "B"
                return 0
            case "C":
                self.state = "D"
                return 3
            case "F":
                self.state = "G"
                return 8
            case "G":
                self.state = "H"
                return 10
            case _:
                raise MealyError("fill", self.state)

    def slur(self):
        match self.state:
            case "B":
                return 2
            case "C":
                self.state = "H"
                return 5
            case "D":
                self.state = "E"
                return 6
            case "E":
                self.state = "F"
                return 7
            case "F":
                self.state = "B"
                return 9
            case "H":
                self.state = "D"
                return 11
            case _:
                raise MealyError("slur", self.state)

    def dash(self):
        match self.state:
            case "B":
                self.state = "C"
                return 1
            case "C":
                self.state = "F"
                return 4
            case _:
                raise MealyError("dash", self.state)


def main():
    return Mealy()


def test_a():
    try:
        Mealy("A").slur()
    except MealyError:
        ...
    try:
        Mealy("A").dash()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("A").slur()
    # with pytest.raises(MealyError):
    #     Mealy("A").dash()
    assert Mealy("A").fill() == 0


def test_b():
    assert Mealy("B").slur() == 2
    assert Mealy("B").dash() == 1
    try:
        Mealy("B").fill()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("B").fill()


def test_c():
    assert Mealy("C").fill() == 3
    assert Mealy("C").dash() == 4
    assert Mealy("C").slur() == 5


def test_d():
    assert Mealy("D").slur() == 6
    try:
        Mealy("D").fill()
    except MealyError:
        ...
    try:
        Mealy("D").dash()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("D").fill()
    # with pytest.raises(MealyError):
    #     Mealy("D").dash()


def test_e():
    assert Mealy("E").slur() == 7
    try:
        Mealy("E").fill()
    except MealyError:
        ...
    try:
        Mealy("E").dash()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("E").fill()
    # with pytest.raises(MealyError):
    #     Mealy("E").dash()


def test_f():
    assert Mealy("F").slur() == 9
    assert Mealy("F").fill() == 8
    try:
        Mealy("F").dash()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("F").dash()


def test_g():
    assert Mealy("G").fill() == 10
    try:
        Mealy("G").dash()
    except MealyError:
        ...
    try:
        Mealy("G").slur()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("G").slur()
    # with pytest.raises(MealyError):
    #     Mealy("GA").dash()


def test_h():
    assert Mealy("H").slur() == 11
    try:
        Mealy("H").fill()
    except MealyError:
        ...
    try:
        Mealy("H").dash()
    except MealyError:
        ...
    # with pytest.raises(MealyError):
    #     Mealy("H").fill()
    # with pytest.raises(MealyError):
    #     Mealy("H").dash()


def test():
    test_a()
    test_b()
    test_c()
    test_d()
    test_e()
    test_f()
    test_g()
    test_h()
    assert isinstance(main(), Mealy)
    assert str(MealyError("slur")) == "slur"

    



# ### Testing
test()

# o = main()
# print("fill ->", o.fill(), "expected", 0) # 0
# print("dash ->", o.dash(), "expected", 1) # 1
# print("fill ->", o.fill(), "expected", 3) # 3
# print("slur ->", o.slur(), "expected", 6) # 6
# print("slur ->", o.slur(), "expected", 7) # 7
# print("slur ->", o.slur(), "expected", 9) # 9
# print("slur ->", o.slur(), "expected", 2) # 2
# print("dash ->", o.dash(), "expected", 1) # 1
# print("dash ->", o.dash(), "expected", 4) # 4
# print("fill ->", o.fill(), "expected", 8) # 8
# print("fill ->", o.fill(), "expected", 10) # 10
# print("slur ->", o.slur(), "expected", 11) # 11
# print("slur ->", o.slur(), "expected", 6) # 6
# try:
#   o.dash()
# except MealyError as e:
#   print("dash ->", e, "expected", "MealyError") # MealyError
# print("slur ->", o.slur(), "expected", 7) # 7

# def test():
#     o = main()
#     assert o.fill() == 0  # 0
#     assert o.dash() == 1  # 1
#     assert o.fill() == 3  # 3
#     assert o.slur() == 6  # 6
#     assert o.slur() == 7  # 7
#     assert o.slur() == 9  # 9
#     assert o.slur() == 2  # 2
#     assert o.dash() == 1  # 1
#     assert o.dash() == 4  # 4
#     assert o.fill() == 8  # 8
#     assert o.fill() == 10  # 10
#     assert o.slur() == 11  # 11
#     assert o.slur() == 6  # 6
#     # with pytest.raises(MealyError):
#     try:
#         o.dash()  # MealyError
#     except MealyError:
#         ...
#     assert o.slur() == 7  # 7

#     o = main()
#     assert o.fill() == 0  # 0
#     assert o.dash() == 1  # 1
#     assert o.dash() == 4  # 4
#     assert o.slur() == 9  # 9
#     assert o.slur() == 2  # 2
#     # with pytest.raises(MealyError):
#     try:
#         o.fill()  # MealyError
#     except MealyError:
#         ...
#     assert o.dash() == 1  # 1
#     assert o.slur() == 5  # 5
#     assert o.slur() == 11  # 11
#     assert o.slur() == 6  # 6
#     assert o.slur() == 7  # 7
#     assert o.fill() == 8  # 8
#     assert o.fill() == 10  # 10
