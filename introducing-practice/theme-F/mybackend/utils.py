from datetime import date, datetime, timedelta

STARTED = date(day=9, month=2, year=2023)



def currentWeek():
  today = date.today()
  count = 1
  next = STARTED + timedelta(days=(8-STARTED.isoweekday()))
  while (today - next).days > 0:
    count +=1
    next += timedelta(7)
  return count



def evenWeek(num=None):
  if num == None:
    return int(currentWeek() % 2 == 0)
  else:
    return int(num % 2 == 0)



def getToday():
  return date.today()


def todayPlus(days):
  return date.today() + timedelta(days=days)


def getTomorrow():
  return todayPlus(1)



def getDayName(day = 0, name = None , nominative = False):
  if nominative:
    days = ["понедельник","вторник","среда","четверг","пятница","суббота"]
  else:
    days = ["понедельник","вторник","среду","четверг","пятницу","субботу"]
  if name == None:
    if day == 0:
      today = date.today().isoweekday()
    else:
      today = day
    day -= 1
    if day in range(len(days)):
      return days[day]
  else:
    for i in range(len(days)):
      if name[:4] == days[i][:4]:
        return i+1
    return 7
  


def getMonthName(month = 0):
  if month == 0:
    month = date.today().month
  if month == 1:
    return "января"
  elif month == 2:
    return "февраля"
  elif month == 3:
    return "марта"
  elif month == 4:
    return "апреля"
  elif month == 5:
    return "мая"
  elif month == 6:
    return "июня"
  elif month == 7:
    return "июля"
  elif month == 8:
    return "августа"
  elif month == 9:
    return "сентября"
  elif month == 10:
    return "октября"
  elif month == 11:
    return "ноября"
  else:
    return "декабря"



def getReadableDates(nextWeek=False):
  if nextWeek:
    firstDay = date.today() + timedelta(days=(8-date.today().isoweekday()))
  else:
    firstDay = date.today() - timedelta(days=date.today().isoweekday()-1)

  today = date.today()
  tomorrow = date.today() + timedelta(days=1)

  rdates = dict(
    today=f"{today.day} {getMonthName(today.month)}",
    tomorrow=f"{tomorrow.day} {getMonthName(tomorrow.month)}",
    week=list()
  )
  for i in range(0,6):
    nd = (firstDay + timedelta(days=i))
    rdates["week"].append(f"{nd.day} {getMonthName(nd.month)}")
  return rdates
  


def getLessonInfo(row):
  # calcrow = 4 + day*14 + number*2 + even*1
  row -= 4 # смещение до первых строк с парами
  day = row // 14
  row = row % 14
  number = row // 2
  even = row % 2
  return dict(day=day+1, number=number+1, even=even)

def t2date(timestamp):
  return datetime.fromtimestamp(timestamp)
