# Написать функцию three_digit, которая определяет является ли произведение цифр заданного числа трехзначным числом
#
# Примеры:
# three_digit(2222) ==> False
# three_digit(2222222) ==> True

import traceback


def three_digit(number):
    # произведение цифр
    mult = 1
    # print(f"Число до: {number}")
    while number > 0:
        mult *= number % 10
        number = number // 10
        # print(f"На очередной итерации число={number}, произведение цифр={mult}")
    # print(f"По итогу произведение цифр: {mult}")
    if len(str(mult)) == 3:
        return True
    else:
        return False


# Тесты
try:
    assert three_digit(2222222) == True
    assert three_digit(9999990) == False
    assert three_digit(0) == False
    assert three_digit(123456) == True
    assert three_digit(999) == True
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")

