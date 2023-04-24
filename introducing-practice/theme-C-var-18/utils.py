def readInt(msg,min=None,max=None):

  if min and max and (min > max):
    raise ValueError("Нижняя граница не может быть больше верхней")

  try:
    num = int(input(msg))
  except ValueError:
    raise TypeError("Произведен некорректный ввод (ожидалось целое число), получена строка")
  
  minok = (num >= min) if min else True
  maxok = (num <= max) if max else True
  if minok and maxok:
    return num
  else:
    rng = "[" + (str(min) if min else "-inf") + "; " + (str(max) if max else "+inf")
    raise ValueError("Значение не попадает в заданный диапазон - {rng}")
  # end of readInt
