from mybackend.utils import *

class Group:

  def __init__(self, name, row, col, book):
    self.name = name
    self.row = row
    self.col = col
    self.book = book
  
  def getLesson(self, day, number, even=None):
    if even == None:
      even = evenWeek()
    number -= 1
    day -= 1

    calcrow = self.row + 2 + day*14 + number*2 + even*1

    title = str(self.book.cell(
      row = calcrow,
      column = self.col
    )).strip().replace("\n","; ")

    if(title != ""):
      kind = str(self.book.cell(
        row = calcrow,
        column = self.col+1
      )).strip().replace("\n","; ")

      teacher = str(self.book.cell(
        row = calcrow,
        column = self.col+2
      )).strip().replace("\n","; ")

      place = str(self.book.cell(
        row = calcrow,
        column = self.col+3
      )).strip().replace("\n","; ")

      return f"{number+1}) {title}, {kind}, {teacher if teacher else '—'}, {place}"
    else:
      return f"{number+1}) —"
    

  """
  Необходимо сформировать расписание:
  - на сегодня
  - на завтра
  - на эту неделю
  - на следующую неделю

  """

  """
  Расписание на сегодня/завтра идет в след. формате, необходимо учитывать четность недели:

  Расписание на число название_месяца:
  1) —
  2) дисциплина, тип_занятия, преподаватель, аудитория
  ...
  6) —
  """
  def getSchedule(self, readableDate=None, day=0, dayNames=False, even=None):
    if day == 0:
      day = getToday().isoweekday()
      readableDate = getReadableDates()["today"]
    elif day == 7:
      day = getTomorrow().isoweekday()
      readableDate = getReadableDates()["tomorrow"]

    sch = f"Расписание на {getDayName(day) if dayNames else ''}{readableDate}:\n" if readableDate else ""
    if day != 8:
      for i in range(1,8):
        sch += self.getLesson(day=day, number=i, even=even) + "\n"
    else:
      sch += "Пар нет\n"
    return sch

  """
  Расписание на неделю оформляется без доп заголовка, идет расписание для всех дней с одной строкой расстояния между днями
  """
  def getWeeklySchedule(self, nextWeek=False):
    rd = getReadableDates(nextWeek=nextWeek)
    sch = f"Расписание на {'следующую ' if nextWeek else ''}неделю:\n\n"
    for (day, name) in enumerate(rd["week"]):
      sch += self.getSchedule(day=day+1, readableDate=name) + "\n"
    return sch
  """
  Расписание на "день недели" подразумевает два расписания - на четную неделю и на нечетную неделю
  """
  def scheduleForDay(self, dayName):
    if dayName == "воскресенье":
      return "Пар нет"
    else:
      day = getDayName(name=dayName)
      sch = f"Расписание для дня ''{dayName}'' (нечетная неделя):\n"
      sch += self.getSchedule(day=day, even=0)
      sch += f"\n\nРасписание для дня ''{dayName}'' (четная неделя):\n"
      sch += self.getSchedule(day=day, even=1)
      return sch