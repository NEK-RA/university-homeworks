"""
Выполняется на основе выполненного задания третьей темы:

- Необходимо создать текстовый файл и реализовать функцию логирования (без использования модуля logging). Функция должна вызываться из каждого метода ранее реализованных классов и записывать в файл строки следующего содержания: КЛЮЧ --- ДАТА И ВРЕМЯ --- КОММЕНТАРИЙ. Ключи: CRE (создание экземпляра класса), INF (изменение), ERR (сработало исключение). Комментарий: создано ..., удален ..., добавлен ..., распечатан ...

- Создать заполненные экземпляры реализованных класса, сериализовать их. В другом питоновском файле импортировать файл с описанием класса и десериализовать объекты. Применить к десериализованным объектам различные методы.
"""

from discipline import Discipline
from academic import Academic
from practice import Practice
from plan import Plan
from utils import log

import pickle

disOk = Discipline("Тестовый предмет", 3, "Тестовая кафедра")

testTime = {'лекция':0,'практическая':0,'лабораторная':0}
acadOk = Academic("Тестовый редмет",1, "Тестовая кафедра", "Тестовый преподаватель", "зачет", testTime)

practOk = Practice("Тестовая практика",1,"Тестовая кафедра","учебная","Тестовый руководитель")

planOk = Plan("0","Тестовый план", ["Тестовая кафедра"], [acadOk], [practOk])

# Ошибки для логов
try:
  Discipline("","","")
except Exception as e:
  log("INF",f"Перехвачено исключение: {e}")


try:
  Academic("",0,"","Преподаватель", "тест", dict())
except Exception as e:
  log("INF",f"Перехвачено исключение: {e}")


try:
  Practice("",0,"","",None)
except Exception as e:
  log("INF",f"Перехвачено исключение: {e}")

try:
  Plan("","","","","")
except Exception as e:
  log("INF",f"Перехвачено исключение: {e}")


# pickle time

with open("task_d118/pickled.data","wb") as data:
  pickle.dump(disOk,data)
  pickle.dump(acadOk,data)
  pickle.dump(practOk,data)
  pickle.dump(planOk,data)
  log("INF","Созданные объекты сохранены в файл с помощью pickle")