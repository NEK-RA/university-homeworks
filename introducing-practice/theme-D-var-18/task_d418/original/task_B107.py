# Написать функцию expanded_form, которая получает число и возвращает строку - сумму слагаемых числа. 
# Между слагаемыми поставить символ +, все отделить пробелами 
#
# Примеры:
# expanded_form(12345) ==> "10000 + 2000 + 300 + 40 + 5"

import traceback


def expanded_form(num):
    # Тело функции
    ns = str(num)
    result = ns[0] + "0"*(len(ns)-1) # Первая цифра

    for i in range(1,len(ns)-1): # Промежуточные при наличии
        if ns[i] == "0":
            continue
        result += " + "
        result += ns[i]
        z = len(ns)-(i+1)
        if z:
            result += "0"*z
    
    if ns[len(ns)-1] != "0": # Последняя цифра при необходимости
        result += " + " + ns[len(ns)-1]
    return result


# Тесты
try:
    assert expanded_form(12345) == "10000 + 2000 + 300 + 40 + 5"
    assert expanded_form(50) == "50"
    assert expanded_form(47) == "40 + 7"
    assert expanded_form(500206) == "500000 + 200 + 6"
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
