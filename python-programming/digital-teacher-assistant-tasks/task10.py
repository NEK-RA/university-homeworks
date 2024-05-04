# 2-е по популярности решение
def remove_empty_and_duplicates(lin):
    lout = []
    for line in lin:
        alt = []
        for val in line:
            if val is not None and val not in alt:
                alt.append(val)
        lout.append(alt)
    return lout


def split_by(lin, sep="|"):
    lout = []
    for line in lin:
        alt = []
        last = None
        for val in line:
            if sep in val:
                last = val.split(sep)[0]
                alt.append(val.split(sep)[1])
            else:
                alt.append(val)
        alt.append(last)
        lout.append(alt)
    return lout


def map_name(name):
    return " ".join([
        word for word in name.split(" ") if not word.endswith(".")
    ])


def map_number(number):
    ob = number.find("(")
    number = number.replace(")", "-")
    nums = number[ob+1:].split("-")
    return f"{nums[0]}-{nums[1]}-{nums[2]}{nums[3]}"


def map_date(date):
    return date.replace("-", "/")


def transform_names(lin):
    for i in range(len(lin)):
        lin[i][0] = map_name(lin[i][0])
    return lin


def transform_numbers(lin):
    for i in range(len(lin)):
        lin[i][1] = map_number(lin[i][1])
    return lin


def transform_dates(lin):
    for i in range(len(lin)):
        lin[i][2] = map_date(lin[i][2])
    return lin


def transpond(matrix):
    transponded = []
    for i in range(len(matrix[0])):
        line = []
        for j in range(len(matrix)):
            line.append(matrix[j][i])
        transponded.append(line)
    return transponded


def main(lin):
    lout = remove_empty_and_duplicates(lin)
    lout = split_by(lout)
    lout = transform_names(lout)
    lout = transform_numbers(lout)
    lout = transform_dates(lout)
    lout = transpond(lout)
    return lout


# testing
print("\n"*9)
list_in = [
  [None, "99-02-15|Антон Н. Тагоцман", "+7(469)061-55-19", None, "+7(469)061-55-19"],
  [None, "02-07-15|Ильдар Е. Неренук", "+7(303)569-59-96", None, "+7(303)569-59-96"],
  [None, "02-07-20|Георгий К. Нирич", "+7(861)727-59-95", None, "+7(861)727-59-95"],
  [None, "00-10-27|Семен Г. Зовисук", "+7(740)286-06-76", None, "+7(740)286-06-76"],
]

list_out_example = [
  ["Антон Тагоцман", "Ильдар Неренук", "Георгий Нирич", "Семен Зовисук"],
  ["469-061-5519", "303-569-5996", "861-727-5995", "740-286-0676"],
  ["99/02/15", "02/07/15", "02/07/20", "00/10/27"]
]

list_out = main(list_in)

print("Input:")
for line in list_in:
  print(line)
print()

print("Expected output:")
for line in list_out_example:
  print(line)
print()

print("Actual output:")
for line in list_out:
  print(line)
print()