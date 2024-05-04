# 3-е по популярности
import struct


def decode_array_of_uint8(data, offset, amount):
    pattern = ">" + "B"*amount
    uint8_tuple = struct.unpack_from(pattern, data, offset)
    return list(uint8_tuple)


def decode_array_of_uint32(data, offset, amount):
    pattern = ">" + "I"*amount
    uint32_tuple = struct.unpack_from(pattern, data, offset)
    return list(uint32_tuple)


def decode_array_of_char(data, offset, amount):
    pattern = ">" + "c"*amount
    char_tuple = struct.unpack_from(pattern, data, offset)
    return "".join([c.decode("utf-8") for c in char_tuple])


signature_format = '>5s'
expected_signature = b"\x41\x57\x46\x4c\x1f"


def validate_signature(data):
    signature = data[:5]
    signature_value = struct.unpack(signature_format, signature)[0]
    if signature_value != expected_signature:
        return ValueError(
            f"Неверная сигнатура: {signature_value}"
            + f", ожидалось {expected_signature}"
        )
    return True


pattern_a = ">IHHIHqb15xHIH"


def decode_struct_a(data, offset=5):
    fields = struct.unpack_from(pattern_a, data, offset)
    a1_addresses = decode_array_of_uint32(
        data=data,
        offset=fields[1],
        amount=fields[0]
    )
    a1 = [decode_struct_b(data, addr) for addr in a1_addresses]
    a2 = decode_array_of_char(data=data, offset=fields[3], amount=fields[2])
    a6 = decode_sturct_c(data, 28)
    a7 = decode_struct_d(data, fields[7])
    a8 = decode_array_of_uint8(data=data, offset=fields[9], amount=fields[8])
    return dict(
        A1=a1,
        A2=a2,
        A3=fields[4],
        A4=fields[5],
        A5=fields[6],
        A6=a6,
        A7=a7,
        A8=a8
    )


pattern_b = ">HH"
size_of_b = 4


def decode_struct_b(data, offset):
    fields = struct.unpack_from(pattern_b, data, offset)
    return dict(
        B1=fields[0],
        B2=fields[1]
    )


pattern_c = ">iBIHI"


def decode_sturct_c(data, offset):
    fields = struct.unpack_from(pattern_c, data, offset)
    с4 = decode_array_of_uint8(data=data, offset=fields[4], amount=fields[3])
    return dict(
        C1=fields[0],
        C2=fields[1],
        C3=fields[2],
        C4=с4
    )


pattern_d = ">biqhQ"


def decode_struct_d(data, offset):
    fields = struct.unpack_from(pattern_d, data, offset)
    return dict(
        D1=fields[0],
        D2=fields[1],
        D3=fields[2],
        D4=fields[3],
        D5=fields[4]
    )


def main(data):
    valid = validate_signature(data)
    if isinstance(valid, ValueError):
        raise valid
    a = decode_struct_a(data, len(expected_signature))
    return a

# # Реализовать разбор двоичного формата данных. 
# # Данные начинаются с сигнатуры 0x41 0x57 0x46 0x4c 0x1f,
# # за которой следует структура A. 
# # Порядок байт: от старшего к младшему. 
# # Адреса указаны в виде смещений от начала данных. 
# # В решении предлагается использовать модуль struct.
# import struct
# # LOG = True
# LOG = False


# # Вспомогательное
# def decode_array_of_uint8(data, offset, amount):
#     pattern = ">" + "B"*amount
#     uint8_tuple = struct.unpack_from(pattern, data, offset)
#     return list(uint8_tuple)


# def decode_array_of_uint32(data, offset, amount):
#     pattern = ">" + "I"*amount
#     uint32_tuple = struct.unpack_from(pattern, data, offset)
#     return list(uint32_tuple)


# def decode_array_of_char(data, offset, amount):
#     pattern = ">" + "c"*amount
#     char_tuple = struct.unpack_from(pattern, data, offset)
#     return "".join([c.decode("utf-8") for c in char_tuple])


# # Данные начинаются с сигнатуры 0x41 0x57 0x46 0x4c 0x1f,

# signature_format = '>5s'
# expected_signature = b"\x41\x57\x46\x4c\x1f"


# def validate_signature(data):
#     signature = data[:5]
#     signature_value = struct.unpack(signature_format, signature)[0]
#     if signature_value != expected_signature:
#         if LOG:
#             print(f'Неверная сигнатура: {signature_value}, ожидалось {expected_signature}')
#         return ValueError(f'Неверная сигнатура: {signature_value}, ожидалось {expected_signature}')
#     if LOG:
#       print(f'Сигнатура: {signature_value} соответствует требуемой')
#     return True
   


# # Структура A
# # Поле	Описание
# # 1	    Размер (uint32) и адрес (uint16) массива адресов (uint32) структур B
# # 2	    Размер (uint16) и адрес (uint32) массива char
# # 3	    uint16
# # 4	    int64
# # 5	    int8
# # 6	    Структура C отступ 5+23=28 байт / сигнатура + поля с первого по 5-е
# # 7	    Адрес (uint16) структуры D
# # 8	    Размер (uint32) и адрес (uint16) массива uint8

# # I - uint32, H - uint16, q - int64, b - int8,  15x - пропуск 15 байтов
# pattern_a = ">IHHIHqb15xHIH"

# def decode_struct_a(data, offset=5):
#   fields = struct.unpack_from(pattern_a, data, offset)
# #   if LOG:
# #      print(f"""
# # A1 - Размер массива адресов структура B - {fields[0]}, адрес их начала - {fields[1]}
# # A2 - Размер массива char - {fields[2]}, адрес его начала - {fields[3]}
# # A3 - Значение поля uint16: {fields[4]}
# # A4 - Значение int64: {fields[5]}
# # A5 - Значение int8: {fields[6]}
# # A6 - Структура С: пропущено
# # A7 - Адрес структуры D - {fields[7]}
# # A8 - Размер массива uint8 - {fields[8]}, адрес его начала - {fields[9]}
# # """)

  

#   a1_addresses = decode_array_of_uint32(data=data, offset=fields[1], amount=fields[0])
#   # if LOG:
#   #   print(f"Адреса структур B для поля A1: {a1_addresses}")
#   a1 = [decode_struct_b(data, addr) for addr in a1_addresses]
#   # if LOG:
#   #   print(f"A1 -> {a1}")

#   a2 = decode_array_of_char(data=data, offset=fields[3], amount=fields[2])
#   # if LOG:
#   #   print(f"A2 -> {a2}")
  
#   a6 = decode_sturct_c(data, 28)
     
#   a7 = decode_struct_d(data, fields[7])

#   a8 = decode_array_of_uint8(data=data, offset=fields[9], amount=fields[8])
#   # if LOG:
#   #   print(f"A8 -> {a8}")

#   return dict(
#     A1=a1,
#     A2=a2,
#     A3=fields[4],
#     A4=fields[5],
#     A5=fields[6],
#     A6=a6,
#     A7=a7,
#     A8=a8
#   )



# # Структура B: (4 байта)
# # Поле	Описание
# # 1	    uint16
# # 2	    uint16

# # H - uint16
# pattern_b = ">HH"
# size_of_b = 4

# def decode_struct_b(data, offset):
#   fields = struct.unpack_from(pattern_b, data, offset)
# #   if LOG:
# #     print(f"""
# # B1 - Значение uint16: {fields[0]}
# # B1 - Значение uint16: {fields[1]}
# # """)
#   return dict(
#     B1=fields[0],
#     B2=fields[1]
#   )



# # Структура C: (15 байт)
# # Поле	Описание
# # 1	    int32
# # 2	    uint8
# # 3	    uint32
# # 4	    Размер (uint16) и адрес (uint32) массива uint8

# # i - int32, B - uint8, I - uint32, H - uint16
# pattern_c = ">iBIHI"

# def decode_sturct_c(data, offset):
#   fields = struct.unpack_from(pattern_c, data, offset)
#   if LOG:
#     print(f"""
# C1 - Значение int32: {fields[0]}
# C2 - Значение uint8: {fields[1]}
# C3 - Значение uint32: {fields[2]}
# C4 - Размер массива uint8 - {fields[3]}, его начало - {fields[4]}
# """)
  
#   с4 = decode_array_of_uint8(data=data, offset=fields[4], amount=fields[3])
#   if LOG:
#     print(f"C4 -> {с4}")

#   return dict(
#     C1=fields[0],
#     C2=fields[1],
#     C3=fields[2],
#     C4=с4
#   )


# # Структура D: (23 байта)
# # Поле	Описание
# # 1	    int8
# # 2	    int32
# # 3	    int64
# # 4	    int16
# # 5	    uint64

# pattern_d = ">biqhQ"

# def decode_struct_d(data, offset):
#   fields = struct.unpack_from(pattern_d, data, offset)
# #   if LOG:
# #     print(f"""
# # D1 - Значение int8: {fields[0]}
# # D2 - Значение int32:  {fields[1]}
# # D3 - Значение int64: {fields[2]}
# # D4 - Значение int16: {fields[3]}
# # D5 - Значение uint64: {fields[4]}
# # """)
#   return dict(
#     D1=fields[0],
#     D2=fields[1],
#     D3=fields[2],
#     D4=fields[3],
#     D5=fields[4]
#   )


# # Общий разбор
# def main(data):
#   valid = validate_signature(data)
#   if LOG:
#     print("Корректная сигнатура?", valid)
  
#   if isinstance(valid, ValueError):
#     raise valid

#   a = decode_struct_a(data, len(expected_signature))
#   if LOG:
#     for key in a:
#       print(f"{key}: {a[key]}")

#   return a

# # Testing

# tests = [
#   dict(
#     test_data = (
#       b'AWFL\x1f\x00\x00\x00\x03\x00?\x00\x02\x00\x00\x00K\xcf\x9aS=\xf1\x8bl'
#       b'\xc1-\x03\xcb\xd6\xbe9\xbd\x0f\xa1\x9c\xb6\xbd\x00\x02\x00\x00\x00M\x00'
#       b"O\x00\x00\x00\x02\x00f'\x02\xe2~\\\xa7\x00\x9e\x0e_2\xd9\x00\x00\x003\x00"
#       b'\x00\x007\x00\x00\x00;lsQ*\xceR^n\xbdk^\xdf\xfc\xa8@\x8fy\xa8ofw\x01er\x1f'
#       b'\x11<6\xbf'
#     ),
#     expected = {
#       'A1': [
#         {'B1': 9986, 'B2': 57982},
#         {'B1': 23719, 'B2': 158},
#         {'B1': 3679, 'B2': 13017}
#       ],
#       'A2': 'ls',
#       'A3': 53146,
#       'A4': 5998215859854716163,
#       'A5': -53,
#       'A6': {
#         'C1': -692176451,
#         'C2': 15,
#         'C3': 2711402173,
#         'C4': [81, 42]
#       },
#     'A7': {
#         'D1': -50,
#         'D2': 1381920445,
#         'D3': 7736867486116646777,
#         'D4': -22417,
#         'D5': 7383371649315180860
#       },
#       'A8': [54, 191]
#     }
#   ),
#   dict(
#     test_data=(b'AWFL\x1f\x00\x00\x00\x03\x00?\x00\x02\x00\x00\x00Ka\xd9E\xc9\xdd#y'
#  b'-\xb6\x0e\xf9\x14\x1f\xed\x9d\x12\xd7\xa1\xc1\x88\x00\x02\x00\x00\x00M\x00'
#  b'O\x00\x00\x00\x02\x00f\xff\xdc\x1c>\xf5#Q\xf4\xca\x1a\xe7\x9f\x00'
#  b'\x00\x003\x00\x00\x007\x00\x00\x00;tx\t\t\xe4\xee\xc3\xbcU\xa4^\xf2\xd0'
#  b'\x8f0\xbd\xe9\xea\x9d\xc6(\xe0\x81p\x87=$\xb8\xf2'),
#     expected={
#       'A1': [
#         {'B1': 65500, 'B2': 7230},
#         {'B1': 62755, 'B2': 20980},
#         {'B1': 51738, 'B2': 59295}
#       ],
#       'A2': 'tx',
#       'A3': 25049,
#       'A4': 5028793603362502158,
#       'A5': -7,
#       'A6': {
#         'C1': 337636765,
#         'C2': 18,
#         'C3': 3617702280,
#         'C4': [9, 9]
#       },
#       'A7': {
#         'D1': -28,
#         'D2': -289162155,
#         'D3': -6602573026109112855,
#         'D4': -5475,
#         'D5': 14278909465121471780
#       },
#       'A8': [184, 242]
#     }
#   )
# ]



# for i, test in enumerate(tests):
#   print("Test", i+1, end=": ")
#   result = main(test["test_data"])
#   print("Совпадает" if result == test["expected"] else "Не совпало :(")