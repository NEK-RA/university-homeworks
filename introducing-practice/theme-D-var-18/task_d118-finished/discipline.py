"""
Создать класс Discipline с полями название, семестр, кафедра. Добавить конструктор класса.
"""
from utils import log

class Discipline:
  title = ""
  sem = 0
  caf = ""

  def __init__(self, name, semester, cafedra):
    if isinstance(name,str) or str(name):
      self.title = str(name)
    else:
      msg = "Переданный аргумент name невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)
    
    if isinstance(semester, int) or int(semester):
      if semester < 1:
        msg = f"Значение {semester} семестра недопустимо"
        log("ERR",msg)
        raise ValueError(msg)
      self.sem = int(semester)
    else:
      msg = "переданный аргумент semester невозможно преобразовать в число"
      log("ERR",msg)
      raise TypeError(msg)

    if isinstance(cafedra,str) or str(cafedra):
      self.caf = str(cafedra)
    else:
      msg = "переданный аргумент cafedra невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)
    
    log("CRE","Создан объект класса Discipline")

  # Конец