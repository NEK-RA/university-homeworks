# Написать функцию is_flush, которая определяет является ли покерная комбинация флэшом
# (5 карт одной масти). Функции на вход приходит список из пяти строк в формате “5H” (5 черви).
# Возможные значения карт: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.
# Возможные масти: Hearts, Spades, Diamonds или Clubs  (обозначаются по первой букве)
#
# Примеры:
# ["AS", "3S", "9S", "KS", "4S"]  ==> true
# ["AD", "4S", "7H", "KS", "10S"] ==> false


import traceback


def is_flush(cards):
    # Тело функции
    result = True
    part = cards[0][1]
    for card in cards:
        if not card.endswith(part):
            result = False
            break
    return result


# Тесты
try:
    assert is_flush(["AS", "3S", "9S", "KS", "4S"]) == True
    assert is_flush(["AD", "4S", "7H", "KC", "5S"]) == False
    assert is_flush(["AD", "4S", "10H", "KC", "5S"]) == False
    assert is_flush(["QD", "4D", "10D", "KD", "5D"]) == True
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")

# print(is_flush(["AS", "3S", "9S", "KS", "4S"]))
