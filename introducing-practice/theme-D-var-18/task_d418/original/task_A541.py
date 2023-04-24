# Создать список (супермаркет), состоящий из словарей (товары). Словари должны содержать как минимум 5 полей
# (например, номер, наименование, отдел продажи, ...). В список добавить хотя бы 10 словарей.
# Конструкция вида:
# market = [{"id":123456, "product":"coca-cola 0.5", "department": "drinks", ...} , {...}, {...}, ...].
# Реализовать функции:
# – вывода информации о всех товарах;
# – вывода информации о товаре по введенному с клавиатуры номеру;
# – вывода количества товаров, продающихся в определенном отделе;
# – обновлении всей информации о товаре по введенному номеру;
# – удалении товара по номеру.
# Провести тестирование функций.

market = [
    {
        "id": 1,
        "product": "coca-cola 0.5",
        "department": "drinks",
        "price": 107.50,
        "weight_kg": 0.5
    },
    {
        "id": 2,
        "product": "fanta 0.3",
        "department": "drinks",
        "price": 95.00,
        "weight_kg": 0.32
    },
    {
        "id": 3,
        "product": "alpengold chocolate",
        "department": "pastry",
        "price": 89.99,
        "weight_kg": 0.045
    },
    {
        "id": 4,
        "product": "bread",
        "department": "bakery",
        "price": 49.50,
        "weight_kg": 0.23
    },
    {
        "id": 5,
        "product": "fruit cake",
        "department": "pastry",
        "price": 775.80,
        "weight_kg": 0.54
    },
    {
        "id": 6,
        "product": "apples",
        "department": "fruits",
        "price": 250.00,
        "weight_kg": 1.0
    },
    {
        "id": 7,
        "product": "mango",
        "department": "fruits",
        "price": 473.20,
        "weight_kg": 1.0
    },
    {
        "id": 8,
        "product": "trout",
        "department": "seafood",
        "price": 1200.00,
        "weight_kg": 1.0
    },
    {
        "id": 9,
        "product": "squid",
        "department": "seafood",
        "price": 649.90,
        "weight_kg": 0.5
    },
    {
        "id": 10,
        "product": "beef",
        "department": "meat",
        "price": 350.00,
        "weight_kg": 1.0
    }
]

# Реализовать функции:
# – вывода информации о всех товарах;
# – вывода информации о товаре по введенному с клавиатуры номеру;
# – вывода количества товаров, продающихся в определенном отделе;
# – обновлении всей информации о товаре по введенному номеру;
# – удалении товара по номеру.

def check_all():
    global market
    print(f"Информация о всех товарах ({len(market)} товаров)\n")
    for item in market:
        print(f"Товар №{item['id']} \"{item['product']}\" находится в отделе {item['department']}. Его масса {item['weight_kg']}кг, а цена {item['price']}у.е.")

def check_by_id():
    global market
    ids = []
    for item in market:
        ids.append(item['id'])
    print(f"Доступные номера товаров: {ids}")
    id = int(input("Укажите номер нужного товара: "))
    if id in ids:
        index = ids.index(id)
        print(f"Товар №{id}:")
        print(f"Наименование: {market[index]['product']}")
        print(f"Отдел: {market[index]['department']}")
        print(f"Цена: {market[index]['price']} у.е.")
        print(f"Вес: {market[index]['weight_kg']} кг")
    else:
        print("Товар с указанным номером отсутствует!")

def amount_in_department():
    global market
    deps = dict()
    for item in market:
        if item['department'] in deps.keys():
            deps[item['department']] += 1
        else:
            deps[item['department']] = 1
    menu = []
    for dep in deps.keys():
        menu.append(dep)
    print("Доступные отделы:")
    for i in range(len(menu)):
        print(f"{i+1}. {menu[i]}")
    choice = int(input("Укажите номер отдела: "))
    if choice in range(1,len(menu)+1):
        print(f"В отделе {menu[choice-1]} находится {deps[menu[choice-1]]} товаров")

def update_info():
    global market
    ids = []
    for item in market:
        ids.append(item['id'])
    print(f"Доступные номера товаров: {ids}")
    id = int(input("Укажите номер нужного товара: "))
    if id in ids:
        index = ids.index(id)
        print(f"Товар №{id}:")
        print(f"Наименование: {market[index]['product']}")
        print(f"Отдел: {market[index]['department']}")
        print(f"Цена: {market[index]['price']} у.е.")
        print(f"Вес: {market[index]['weight_kg']} кг")

        prod = input("Укажите новое наименование товара: ")
        dep = input("Укажите отдел, в котором находится продукт: ")
        price = float(input("Укажите цену продукта в у.е.: "))
        weight = float(input("Укажите вес товара в кг: "))

        market[index]['product'] = prod
        market[index]['department'] = dep
        market[index]['price'] = price
        market[index]['weight_kg'] = weight

        print("Информация о товаре после изменения данных:")
        print(f"Товар №{id}:")
        print(f"Наименование: {market[index]['product']}")
        print(f"Отдел: {market[index]['department']}")
        print(f"Цена: {market[index]['price']} у.е.")
        print(f"Вес: {market[index]['weight_kg']} кг")

    else:
        print("Товар с указанным номером отсутствует!")

def delete_item():
    global market
    ids = []
    for item in market:
        ids.append(item['id'])
    print(f"Доступные номера товаров: {ids}")
    id = int(input("Укажите номер нужного товара: "))
    if id in ids:
        market.remove(market[ids.index(id)])
        print("Товар удален!")
    else:
        print("Товар с указанным номером отсутствует!")

def main():
    menu = "Меню:\n" +\
        "1. Вывод информации о всех товарах\n" +\
        "2. Информация о товаре по номеру\n" +\
        "3. Кол-во товаров в указанном отделе\n" +\
        "4. Обновление информации о товаре по номеру\n" +\
        "5. Удаление товара по номеру\n" +\
        "0. Завершение работы\n" +\
        "Ваш выбор: "
    choice = -1
    while choice != 0:
        print("\n"*5)
        choice = int(input(menu))
        if choice == 1:
            check_all()
        elif choice == 2:
            check_by_id()
        elif choice == 3:
            amount_in_department()
        elif choice == 4:
            update_info()
        elif choice == 5:
            delete_item()
        elif choice == 0:
            print("Спасибо, что выбираете нас!")
        else:
            print("Выбранный пункт отсутствует в меню!!!")

main()