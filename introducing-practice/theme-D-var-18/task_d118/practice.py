"""
Создать производный от Discipline класс Practice. Новые поля: 
- вид практики (учебная/производственная/преддипломная),
- руководитель практики, 
- тематика практики (список тем). 
Определить конструктор, с вызовом родительского конструктора. Определить функции
- изменения руководителя, 
- добавления, удаления и изменения тематики.
- Переопределить метод преобразования в строку для печати основной информации (название, вид практики, семестр, кафедра, руководитель).
"""
from discipline import Discipline
from utils import log

class Practice(Discipline):
  kind = 0
  lead = ""
  theme = "Отсутствует"

  def __init__(self, name, semester, cafedra, prType, leader):
    # родительский объект
    super().__init__(name,semester,cafedra)

    # тип практики
    availablePr = ["учебная", "производственная", "преддипломная"]
    if isinstance(prType,str) or str(prType):
      prType = str(prType).lower()

      if prType.lower() in availablePr:
        if prType == availablePr[0]:
          self.kind = 0
        elif prType == availablePr[1]:
          self.kind = 1
        else:
          self.kind = 2
      else:
        msg = f"{prType} не является допустимым значением (допустимые: {availablePr})"
        log("ERR",msg)
        raise ValueError(msg)
    else:
      msg = "переданный аргумент prType невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)
    log("CRE", "Создан объект класса Practice")
    
    # руководитель
    if isinstance(leader,str) or str(leader):
      self.lead = str(leader)
    else:
      msg = "переданный аргумент leader невозможно преобразовать к строке"
      log("ERR",msg)
      raise TypeError(msg)


  def changeLeader(self, name):
    if isinstance(name,str) or str(name):
      log("INF", f"Руководитель практики сменен с {self.lead} на {name}")
      self.lead = str(name)
    else:
      msg = "переданный аргумент name невозможно преобразовать к строке"
      log("ERR", msg)
      raise TypeError(msg)
  

  def changeTheme(self, topic):
    if isinstance(topic,str) or str(topic):
      log("INF",f"Тема практики {self.title} сменена с {self.theme} на {topic}")
      self.theme = str(topic)
    else:
      msg = "переданный аргумент topic невозможно преобразовать к строке"
      log("ERR", msg)
      raise TypeError(msg)
  

  def addTheme(self, topic):
    if self.theme != "Отсутствует":
      self.changeTheme(self.theme + "; " + topic)
    else:
      self.changeTheme(topic)
  

  def removeTheme(self):
    self.theme = "Отсутствует"
    log("INF",f"Тема практики удалена")


  @property
  def practiceType(self):
    availablePr = ["учебная", "производственная", "преддипломная"]
    return availablePr[self.kind]


  def __str__(self):
    log("INF","Запрошена информация о практике")
    return f"""
    Информация о практике:

    Наименование: {self.title}
    Тип: {self.practiceType}
    Семестр: {self.sem}
    Кафедра: {self.caf}
    Руководитель: {self.lead}
    Тема: {self.theme}
    """


  # Конец




