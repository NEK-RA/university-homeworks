# Написать функцию highest_rank(arr), которая возвращает самое часто встречающееся число в списке,
# если таких чисел несколько - вернуть наибольшее.
#
# Пример:
# highest_rank([1,0,1,0,1,0,1) => 1


import traceback


def highest_rank(arr):
    # Тело функции
    rank = dict()
    for num in arr:
        if num not in rank.keys():
            rank[num] = 1
        else:
            rank[num] += 1
    maxnum = None
    maxcount = 0
    for key in rank.keys():
        # print(f"{key} found {rank[key]} times")
        if rank[key] >= maxcount:
            if rank[key] > maxcount:
                maxnum = key
                maxcount = rank[key]
            else:
                if key > maxnum:
                    maxnum = key
                    maxcount = rank[key]
    # ПРИМЕЧАНИЕ: можно использовать set чтобы получить набор чисел и потом у списка юзать count чтобы узнать кол-во
    return maxnum


# Тесты
try:
    assert highest_rank([12, 10, 8, 12, 7, 6, 4, 10, 12]) == 12
    assert highest_rank([2, 10, 8, 2, 7, 6, 4, 10, 2, 10]) == 10
    assert highest_rank([12, 10, 8, 8, 3, 3, 3, 3, 2, 4, 10, 12, 10]) == 3
    assert highest_rank([1, 2, -3, 1, 2, -3, 1, 2, -3, 1, 2, -3]) == 2
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")

# print(highest_rank([2, 10, 8, 2, 7, 6, 4, 10, 2, 10]))