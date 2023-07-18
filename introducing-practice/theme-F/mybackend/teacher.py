from mybackend.utils import *

class Teacher:
  def __init__(self, name, book):
    self.name = name    
    self.schedule = dict()
    days = ["понедельник", "вторник", "среда", "четверг", "пятница", "суббота"]
    for day in days:
      self.schedule[day] = {
        "1": {"odd":None,"even":None},
        "2": {"odd":None,"even":None},
        "3": {"odd":None,"even":None},
        "4": {"odd":None,"even":None},
        "5": {"odd":None,"even":None},
        "6": {"odd":None,"even":None},
        "7": {"odd":None,"even":None}
      }
    self.book = book
  


  def count(self, lesson):
    kind = str(self.book.cell(row=lesson["row"], column=lesson["column"]-1)).strip()
    title = str(self.book.cell(row=lesson["row"], column=lesson["column"]-2)).strip()
    place = str(self.book.cell(row=lesson["row"], column=lesson["column"]+1)).strip()
    info = getLessonInfo(lesson["row"])
    dayName = getDayName(day=info["day"], nominative=True)
    number = str(info["number"])
    even = "even" if info["even"] else "odd"
    group = str(self.book.cell(row=2, column=lesson["column"]-2)).strip()
    lesson = self.schedule[dayName][number][even]
    if lesson == None:
      self.schedule[dayName][number][even] = dict(title=title, kind=kind, group=group, place=place)
    else:
      self.schedule[dayName][number][even]["group"] += ", " + group



  def getLesson(self, day, number, even=None):
    if even == None:
      even = "even" if evenWeek() else "odd"
    dayName = getDayName(day=day, nominative=True)
    lesson = self.schedule[dayName][str(number)][even]
    if lesson:
      return f"{number}) {lesson['title']}, {lesson['kind']}, {lesson['group']}, {lesson['place']}"
    else:
      return f"{number}) —"
    


  def getSchedule(self, readableDate=None, day=0, dayNames=False, even=None):
    if day == 0:
      day = getToday().isoweekday()
      readableDate = getReadableDates()["today"]
    elif day == 7:
      day = getTomorrow().isoweekday()
      readableDate = getReadableDates()["tomorrow"]

    sch = f"Расписание преподавателя {self.name} на {getDayName(day) if dayNames else ''}{readableDate}:\n" if readableDate else ""
    if day != 8:
      for i in range(1,8):
        sch += self.getLesson(day=day, number=i, even=even) + "\n"
    else:
      sch += "Пар нет\n"
    return sch
  


  def getWeeklySchedule(self, nextWeek=False):
    rd = getReadableDates(nextWeek=nextWeek)
    sch = f"Расписание на {'следующую ' if nextWeek else ''}неделю:\n\n"
    for (day, name) in enumerate(rd["week"]):
      sch += self.getSchedule(day=day+1, readableDate=name) + "\n"
    return sch
  


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