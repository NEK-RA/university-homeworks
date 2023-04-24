# Написать функцию next_version, которая будет принимать строку (текущая версия программного обеспечения)
# и будет возвращать строку, содержащую следующий номер версии.
# Правила:
# все числа, кроме первого, должны быть меньше 10
# если после увеличения они становятся равными 10 - установите их в 0 и последовательно увеличите следующий номер
#
# Пример:
# next_version("1.2.3") ==> "1.2.4"
# next_version("0.9.9") ==> "1.0.0"


import traceback


def next_version(s):
    # Тело функции

    # Лайфхак: можно убрать точки в строке, сохранять длинну строки, переводить строку в число и прибавлять единицу. А потом обратное преобразование в строку и со вставкой точек

    if len(s) == 1:
        return str(int(s)+1)
    
    parts = s.split(".")
    parts = list(map(int,parts))[::-1]
    inc = True

    for i in range(len(parts)-1):
        if inc:
            if parts[i] != 9:
                parts[i] += 1
                inc = False
            else:
                parts[i] = 0
                inc = True

    if inc:
        parts[len(parts)-1] += 1

    result = ".".join(list(map(str,parts[::-1])))
    return result


# Тесты
try:
    assert next_version("1.2.3") == "1.2.4"
    assert next_version("0.9.9") == "1.0.0"
    assert next_version("1") == "2"
    assert next_version("1.2.3.4.5.6.7.8") == "1.2.3.4.5.6.7.9"
    assert next_version("9.9") == "10.0"
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")

