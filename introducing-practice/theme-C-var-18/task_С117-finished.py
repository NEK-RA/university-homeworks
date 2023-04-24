"""
Каждый класс реализовать в отдельном модуле, импортируя их в производные модули.

ОПИСАНИЯ КЛАССОВ ПЕРЕНЕСЕНЫ В МОДУЛИ

Создать класс Discipline - discipline.py
Создать производный от Discipline класс Academic - academic.py
Создать производный от Discipline класс Practice - practice.py
Создать класс Plan - plan.py

Предусмотреть хотя бы в 3 местах обработку возможных исключений.
В каждом модуле провести подробное тестирование всех создаваемых объектов и функций.
"""

from discipline import Discipline
from academic import Academic
from practice import Practice
from plan import Plan
from utils import readInt

def main():
  plans = []
  choice = -1
  menu = \
"""
1. Добавить учебный план
2. Перейти в меню учебного плана
3. Удалить учебный план
0. Выйти из программы  
"""
  while choice != 0:
    try:
      choice = readInt(f"{menu}\nВыберите пункт меню: ", 0, 3)
    except ValueError as ve:
      print(ve)
      continue
    except TypeError as te:
      print(te)
      continue
    # Добавление учебного плана
    if choice == 1:
      print("-"*20)
      code = input("Код направления: ")
      name = input("Наименование направления: ")
      plans.append(Plan(code,name,[],[],[]))
      print("-"*20)

    # Редактирование
    elif choice == 2:
      print("-"*20)
      print("Список учебных планов: ")
      for index, plan in enumerate(plans):
        print(f"{index}. {plan.code} - {plan.title}")
      
      try:
        index = readInt(f"Укажите индекс редактируемого плана: ", 0, len(plans)-1)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue
      
      editPlan(plans[index])
      print("-"*20)

    # Удаление
    elif choice == 3:
      print("-"*20)
      print("Список учебных планов: ")
      for index, plan in enumerate(plans):
        print(f"№{index}) {plan.code} - {plan.title}")
      
      try:
        index = readInt(f"Укажите индекс удаляемого плана: ", 0, len(plans)-1)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue

      del plans[index]

      print("-"*20)

    else:
      # остается только 0 = выход
      break
# end of main

def editPlan(plan: Plan):
  choice = -1
  print(f"Меню редактирования | {plan.code} - {plan.title}")
  menu = \
  """
  1. Добавить кафедру
  2. Удалить кафедру
  3. Добавить академ.предмет
  4. Добавить практику
  5. Отобразить предметы и практики
  6. Изменить предмет или практику
  7. Удалить предмет или практику
  8. Сохранить в файл
  0. Выход
  """
  while choice != 0:
    try:
      choice = readInt(f"{menu}\nВыберите пункт меню: ", 0, 8)
    except ValueError as ve:
      print(ve)
      continue
    except TypeError as te:
      print(te)
      continue

    # Добавление кафедры
    if choice == 1:
      plan.cafs.append(input("Название кафедры: "))

    # удаление кафедры
    elif choice == 2:
      for i,caf in enumerate(plan.cafs):
        print(f"{i}) {caf}")
      try:
        index = readInt(f"Укажите индекс удаляемой кафедры: ", 0, len(plan.cafs)-1)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue

      del plan.cafs[index]

    # добавить академ предмет
    elif choice == 3:

      subject = input("Название предмета: ")
      
      semester = 0
      while (semester not in range(1,11)):
        try:
          semester = readInt("Номер семестра: ",1,10)
        except ValueError as ve:
          print(ve)
          continue
        except TypeError as te:
          print(te)
          continue
      
      caf = ""
      while caf not in plan.cafs:
        print(f"Укажите ответственную кафедру из списка {plan.cafs}")
        caf = input("Кафедра: ")
      
      teacher = input("Имя преподавателя: ")

      control = input("Укажите форму успеваемости: ")
      times = {'лекция':-1, 'практическая':-1, 'лабораторная':-1}
      
      while(times['лекция'] < 0):
        try:
          times['лекция'] = readInt("Кол-во часов для занятий типа 'лекция': ",min=0)
        except ValueError as ve:
          print(ve)
          continue
        except TypeError as te:
          print(te)
          continue

      while(times['практическая'] < 0):
        try:
          times['практическая'] = readInt("Кол-во часов для занятий типа 'практическая': ",min=0)
        except ValueError as ve:
          print(ve)
          continue
        except TypeError as te:
          print(te)
          continue

      while(times['лабораторная'] < 0):
        try:
          times['лабораторная'] = readInt("Кол-во часов для занятий типа 'лабораторная': ",min=0)
        except ValueError as ve:
          print(ve)
          continue
        except TypeError as te:
          print(te)
          continue
      try:
        subj = Academic(subject=subject,semester=semester,caf=caf,teacher=teacher,control=control,times=times)
      except Exception as e:
        print(e)
        print("Не удалось создать предмет")
        continue
      plan = plan + subject

    # добавить практику
    elif choice == 4:
      
      subject = input("Название предмета: ")
      
      semester = 0
      while (semester not in range(1,11)):
        try:
          semester = readInt("Номер семестра: ",1,10)
        except ValueError as ve:
          print(ve)
          continue
        except TypeError as te:
          print(te)
          continue
      
      caf = ""
      while caf not in plan.cafs:
        print(f"Укажите ответственную кафедру из списка {plan.cafs}")
        caf = input("Кафедра: ")
      
      availablePr = ["учебная", "производственная", "преддипломная"]
      pr = ""
      while pr not in availablePr:
        print(f"Укажите тип практики, допустимые значения: {availablePr}")
        pr = input("Тип: ")
      
      lead = input("Руководитель: ")
      try:
        pract = Practice(name=subject, semester=semester,cafedra=caf, prType=pr, leader=lead)
      except Exception as e:
        print(e)
        print("Не удалось оформить практику")

      plan.practics.append(pract)

    # показать практики и предметы
    elif choice == 5:
      for i in range(len(plan)):
        print(plan[i])
    # изменить предмет или практику
    elif choice == 6:
      for i in range(len(plan)):
        print(f"{i}) {plan[i]}")
      try:
        index = readInt(f"Укажите индекс редактируемой дисциплины: ", 0, len(plan)-1)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue
      editDiscipline(plan[index])

    # удалить предмет или практику
    elif choice == 7:
      for i in range(len(plan)):
        print(f"{i}) {plan[i]}")
      try:
        index = readInt(f"Укажите индекс редактируемой дисциплины: ", 0, len(plan)-1)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue
      plan = plan - plan[index]

    # сохранить в файл
    elif choice == 8:
      plan.writeTxt()
    else:
      # Выход
      break


def editDiscipline(discipline):
  if isinstance(discipline,Academic):
    menu = \
    """
    1. Изменить преподавателя
    2. Изменить форму контроля
    0. Выход
    """
    choice = -1
    while choice != 0:
      try:
        choice = readInt(f"{menu}\nВыберите пункт меню: ", 0, 2)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue
      if choice == 1:
        teacher = input("Новый преподаватель: ")
        discipline.changeTutor(teacher)
      elif choice == 2:
        control = input("Укажите форму успеваемости")
        discipline.changeTest(control)
      else:
        break
    
  elif isinstance(discipline, Practice):
    menu = \
    """
    1. Добавить тематику
    2. Изменить тематику
    3. Удалить тематику
    4. Изменить руководителя
    0. Выход
    """
    choice = -1
    while choice != 0:
      try:
        choice = readInt(f"{menu}\nВыберите пункт меню: ", 0, 4)
      except ValueError as ve:
        print(ve)
        continue
      except TypeError as te:
        print(te)
        continue
      if choice == 1:
        topic = input("Новая тематика: ")
        discipline.addTheme(topic)
      elif choice == 2:
        topic = input("Смена темы: ")
        discipline.changeTheme(topic)
      elif choice == 3:
        discipline.removeTheme()
      elif choice == 4:
        teacher = input("Новый руководитель: ")
        discipline.changeLeader(teacher)
      else:
        break


main()

