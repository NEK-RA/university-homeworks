"""
Создать класс Plan. Поля: 
- код направления,
- название направления, 
- название кафедр,
- список основных дисциплин (список экземпляров класса Academic), 
- список практик (список экземпляров класса Practice). 
Определить конструктор.

- Переопределить метод преобразования в строку для печати всей информации об учебном плане (с использованием переопределения в классах Academic и Practice). 
- Переопределить методы получения количества дисциплин функцией len (пусть вначале идут индексы основных дисциплин, затем практик)
- Метод получения дисциплины по индексу
- Метод изменения дисциплины по индексу
- Метод удаления дисциплины по индексу

Переопределить операции + и - для добавления или удаления дисциплины. 
Добавить функцию создания txt-файла и записи всей информации в него (в том числе количество часов и тематику практик).
"""
from discipline import Discipline
from academic import Academic
from practice import Practice

class Plan:
  code = ""
  title = ""
  cafs = []
  subjects = [] # Academic
  practics = [] # Practice


  def __init__(self,dcode, dtitle, dcafs, dsubjects, dpracts):
    # код направления
    if isinstance(dcode,str) or str(dcode):
      self.code = str(dcode)
    else:
      raise TypeError("параметр переданный в dcode невозможно преобразовать к строке")

    # наименование направления
    if isinstance(dtitle,str) or str(dtitle):
      self.title = str(dtitle)
    else:
      raise TypeError("параметр переданный в dcode невозможно преобразовать к строке")
    
    # кафедры
    if isinstance(dcafs,str) or str(dcafs):
      dcafs = str(dcafs)
      parts = dcafs.split(",")
      if len(parts) == 1:
        self.cafs = parts
      else:
        self.cafs = [i for i in parts if len(i)>0]
    else:
      raise TypeError("параметр переданный в dcode невозможно преобразовать к строке")

    # предметы
    if isinstance(dsubjects,list):
      ok = True
      for item in dsubjects:
        if not isinstance(item,Academic):
          ok = False
          break
      if ok:
        self.subjects = dsubjects
      else:
        raise ValueError("список, переданный в dsubjects, содержит записи, не являющиеся академ. предметами")
    else:
      raise TypeError("параметр переданный в dsubjects должен являться списком")

    # практики
    if isinstance(dpracts,list):
      ok = True
      for item in dpracts:
        if not isinstance(item,Practice):
          ok = False
          break
      if ok:
        self.practics = dpracts
      else:
        raise ValueError("список, переданный в dpracts, содержит записи, не являющиеся каким-либо видом практики")
    else:
      raise TypeError("параметр переданный в dpracts должен являться списком")


  def __len__(self):
    dsc = list()
    dsc.extend(self.subjects)
    dsc.extend(self.practics)
    return len(dsc)


  def __getitem__(self,index):
    dsc = list()
    dsc.extend(self.subjects)
    dsc.extend(self.practics)
    if index in range(len(dsc)):
      return dsc[index]
    else:
      raise IndexError(f"Переданный индекс {index} не попадает в диапазон [0;{len(dsc)-1}]")


  def __setitem__(self, index, discipline):
    if isinstance(discipline, Discipline):
      dsc = list()
      dsc.extend(self.subjects)
      dsc.extend(self.practics)
      if index in range(len(dsc)):
        if index in range(len(self.subjects)):
          self.subjects[index] = discipline
        else:
          index -= len(self.subjects)
          self.practics[index] = discipline
      else:
        raise IndexError(f"Переданный индекс {index} не попадает в диапазон [0;{len(dsc)-1}]")
    else:
      raise TypeError("Присваиваемое значение не является дисциплиной")


  def __delitem__(self, index):
    dsc = list()
    dsc.extend(self.subjects)
    dsc.extend(self.practics)
    if index in range(len(dsc)):
      if index in range(len(self.subjects)):
        self.subjects.pop(index)
      else:
        index -= len(self.subjects)
        self.practics.pop(index)
    else:
      raise IndexError(f"Переданный индекс {index} не попадает в диапазон [0;{len(dsc)-1}]")


  def __add__(self,discipline):
    if isinstance(discipline, Discipline):
      if isinstance(discipline, Academic):
        self.subjects.append(discipline)
      elif isinstance(discipline, Practice):
        self.practics.append(discipline)
      else:
        print("Неизвестный тип дисциплины, добавление не было произведено")
    else:
      raise TypeError("Добавляемое значение не является дисциплиной")
    return self


  def __sub__(self, discipline):
    if isinstance(discipline, Discipline):
      src = list()
      subjindex = -1
      practindex = -1

      if isinstance(discipline, Academic):
        src.extend(self.subjects)
        for i in range(len(src)):
          sameTitle = discipline.title == src[i].title
          sameSem = discipline.sem == src[i].sem
          sameCaf = discipline.caf == src[i].caf
          sameTutor = discipline.tutor == src[i].tutor
          sameTest = discipline.test == src[i].test
          sameTime = discipline.time == src[i].time
          allTrue = sameTitle and sameSem and sameCaf\
                  and sameTutor and sameTest and sameTime
          if allTrue:
            subjindex = i
            break

      elif isinstance(discipline, Practice):
        src.extend(self.practics)
        for i in range(len(src)):
          sameTitle = discipline.title == src[i].title
          sameSem = discipline.sem == src[i].sem
          sameCaf = discipline.caf == src[i].caf
          sameKind = discipline.kind == src[i].kind
          sameLead = discipline.lead == src[i].lead
          sameTheme = discipline.theme == src[i].theme
          allTrue = sameTitle and sameSem and sameCaf\
                  and sameKind and sameLead and sameTheme
          if allTrue:
            practindex = i
            break
      else:
        raise TypeError("Вычитается неизвестный тип дисциплины, операция невозможна")
      
      if subjindex != -1:
        self.subjects.pop(subjindex)
      elif practindex != -1:
        self.practics.pop(practindex)
      else:
        raise ValueError("В плане нет вычитаемой дисциплины")
    else:
      raise TypeError("Вычитаемое значение не является дисциплиной")
    return self


  def __str__(self):
    content = f"----------\n"
    content += f"Код дисциплины: {self.code}\n"
    content += f"Наименование дисциплины: {self.title}\n"
    content += f"Выпускающие кафедры: {', '.join(self.cafs)}"
    content += f"----------\n"

    content += f"\nАкадемические предметы:\n"
    for subj in self.subjects:
      content += f"{str(subj)}\n"
    content += f"----------\n"

    content += f"\nПрактики:\n"
    for subj in self.practics:
      content += f"- {str(subj)}\n"
    content += f"----------\n"
    return content


  def writeTxt(self,filename=None):
    if filename == None:
      filename = f"{self.code}_{self.title}_Учебный_План.txt"
    with open(filename,"w") as file:
      file.write(str(self))


# Конец
