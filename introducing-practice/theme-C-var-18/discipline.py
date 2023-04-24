"""
Создать класс Discipline с полями название, семестр, кафедра. Добавить конструктор класса.
"""

class Discipline:
  title = ""
  sem = 0
  caf = ""

  def __init__(self, name, semester, cafedra):
    if isinstance(name,str) or str(name):
      self.title = str(name)
    else:
      raise TypeError("переданный аргумент name невозможно преобразовать к строке")
    
    if isinstance(semester, int) or int(semester):
      if semester < 1:
        raise ValueError(f"Значение {semester} семестра недопустимо")
      self.sem = int(semester)
    else:
      raise TypeError("переданный аргумент semester невозможно преобразовать в число")

    if isinstance(cafedra,str) or str(cafedra):
      self.caf = str(cafedra)
    else:
      raise TypeError("переданный аргумент cafedra невозможно преобразовать к строке")

  # Конец