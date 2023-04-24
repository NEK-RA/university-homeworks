# Цена телефонного звонка следующая:
# первая минута звонка стоит min1 рублей,
# минута со второй по 10 включительно стоит min2_10 рублей,
# а начиная с 11 минуты – min11 рублей.
# Написать функцию phone_call(min1, min2_10, min11, s),
# которая возвращает максимальную длительность разговора,
# которую можно совершить, если на счету s рублей
#
# Пример:
# phone_call(3, 1, 2, 20) ==> 14

import traceback


def phone_call(min1, min2_10, min11, s):
    # Тело функции
    result = 0
    min2_10_break = False
    # print(f"s={s}")
    if s >= min1:
        result += 1
        s -= min1
    # print(f"После {result}й минуты s={s}")
    for i in range(9):
        if s >= min2_10:
            result += 1
            s -= min2_10
        else:
            min2_10_break = True
            break
        # print(f"После {result}й минуты s={s}")
    if s >= min11 and not min2_10_break:
        while s >= min11:
            result += 1
            s -= min11
            # print(f"После {result}й минуты s={s}")

    return result


# # Тесты
try:
    assert phone_call(3,1,2,20) == 14
    assert phone_call(10,1,2,22) == 11
    assert phone_call(2,2,1,2) == 1
    assert phone_call(1,2,1,6) == 3
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")

# print(phone_call(1,2,1,6))
