"""
Создать производный от Discipline класс Academic. Новые поля: 
- преподаватель,
- форма контроля (зачет или экзамен),
- часы (словарь вида форма занятия (лекция/лабораторная/практическая): количество занятий). Определить конструктор, с вызовом родительского конструктора. 
Определить функции
- изменения преподавателя
- изменения формы контроля,
- форматированной печати количества занятий различного вида. 
- Переопределить метод преобразования в строку для печати основной информации (название, семестр, кафедра, преподаватель, форма контроля).
"""
from discipline import Discipline
from utils import log

class Academic(Discipline):
  tutor = ""
  test = 0 # 0=зачет, 1=экзамен
  time = {"лекция": 0, "практическая": 0, "лабораторная": 0}

  def __init__(self, subject, semester, caf, teacher, control, times):
    # родительский объект
    super().__init__(subject, semester, caf)
    
    # имя преподавателя
    if isinstance(teacher,str) or str(teacher):
      self.tutor = str(teacher)
    else:
      msg = "переданный аргумент teacher невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)
    
    # тип тестирования
    if isinstance(control,str) or str(control):
      control = str(control)
      if control.lower() in ["зачет", "экзамен"]:
        self.test = 0 if control == "зачет" else 1
      else:
        msg = f"{control} не является допустимым значением (допустимые: зачет, экзамен)"
        log("ERR",msg)
        raise ValueError(msg)
    else:
      msg = "переданный аргумент control невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)
    
    # часы 
    if isinstance(times,dict):

      typelk = "лекция" in times.keys()
      typepr = "практическая" in times.keys()
      typelab = "лабораторная" in times.keys()

      if typelk and typepr and typelab:
        self.time['лекция'] = times['лекция']
        self.time['практическая'] = times['практическая']
        self.time['лабораторная'] = times['лабораторная']
      else:
        msg = f"В словаре times присутствуют ключи {times.keys()}, хотя должны присутствовать: 'лекция', 'практическая', 'лабораторная'"
        log("ERR", msg)
        raise ValueError(msg)
    else:
      msg = f"переданный аргумент times является объектом типа {type(times)}, но нужен тип {type(dict)}"
      log("ERR", msg)
      raise TypeError(msg)
    log("CRE","Создан объект класса Academic")


  def changeTutor(self,name):
    # имя преподавателя
    if isinstance(name,str) or str(name):
      log("INF",f"Имя преподавателя изменено: с {self.tutor} на {name}")
      self.tutor = str(name)
    else:
      msg = "переданный аргумент name невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)


  def changeTest(self,control):
    # тип тестирования
    if isinstance(control,str) or str(control):
      control = str(control)
      if control.lower() in ["зачет", "экзамен"]:
        self.test = 0 if control == "зачет" else 1
        log("INF",f"Форма контроля изменена на {self.testType}")
      else:
        msg = f"{control} не является допустимым значением (допустимые: зачет, экзамен)"
        log("ERR", msg)
        raise ValueError(msg)
    else:
      msg = "переданный аргумент control невозможно преобразовать к строке"
      log("ERR", msg)
      raise TypeError(msg)


  def printTimes(self):
    out = f"""
    Часы занятий:
      - Лекции: {self.time['лекция']} академ. часов
      - Практические: {self.time['практическая']} академ. часов
      - Лабораторные: {self.time['лабораторная']} акакдем. часов
    """
    print(out)
    log("INF",f"Распечатаны часы занятий для дисциплины {self.title}")


  @property
  def testType(self):
    if self.test:
      return "экзамен"
    else:
      return "зачет"


  def __str__(self):
    log("INF","Запрошена информация о дисциплине")
    return f"""
    Информация о дисциплине:

    Наименование: {self.title}
    Семестр: {self.sem}
    От кафедры: {self.caf}
    Ведет: {self.tutor}
    Форма контроля: {self.testType}
    """
  # Конец