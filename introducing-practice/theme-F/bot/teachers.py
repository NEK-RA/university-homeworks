import re

from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.utils import get_random_id

def findTeacher(bot,event):
    rawargs = event.text.split(" ")
    if len(rawargs) == 1:
      args = rawargs
    else:
      args = [rawargs[0], " ".join(rawargs[1:])]
    kb = bot.default
    if args[0].lower() == "найти":
      if len(args) == 1:
        text = "Используйте следующий формат:\n\"найти Ива\"\nили\n\"найти Иванов И.И.\"\n----------\nP.S.: кавычки, очевидно, добавлять не нужно\nрегистр текста значения не имеет"
      elif len(args) == 2:
        results = bot.sch.rawTeachers(args[1])
        if len(results) == 0:
          text = "Преподаватель не был найден"
        elif len(results) == 1:
          bot.users[str(event.user_id)]["search"] = results[0]
          text = "Показать расписание преподавателя " + results[0]
          kb = VkKeyboard(one_time=True)
          kb.add_button("Сегодня")
          kb.add_button("Завтра")
          kb.add_line()
          kb.add_button("На эту неделю")
          kb.add_button("На след. неделю")
          kb = kb.get_keyboard()
        elif len(results) > 1 and len(results) <= 6:
          text = "Выберите преподавателя"
          kb = VkKeyboard(one_time=True)
          for i in range(len(results)):
            if i % 2 == 1:
              kb.add_line()
            kb.add_button(f"Найти {results[i]}")
          print("kb before:", kb)
          kb = kb.get_keyboard()
          print("kb after:", kb)
        else:
          text = "По вашему запросу найдено слишком много преподавателей:\n{}\nПожалуйста уточните фамилию".format(*results)
      else:
        text = "Кажется что-то пошло не так. Информация об ошибке: метод findTeacher из TEACHERS_HANDLERS получил слишком много аргументов"
      bot.api.messages.send(
        user_id=event.user_id,
        random_id=get_random_id(),
        message=text,
        keyboard=kb
      )
      return True
      

  
def findToday(bot,event):
    cm = re.match(r"^сегодня$", event.text.lower())
    fio = bot.users[str(event.user_id)]["search"]
    prev = bot.users[str(event.user_id)]["last_msg"]
    pm = prev.lower() != "бот" and prev.lower() != "погода"
    if cm and pm:
      bot.users[str(event.user_id)]["search"] = ""
      if fio in bot.sch.teachers:
        text = bot.sch.teachers[fio].getSchedule(day=0)
      else:
        text = "Преподаватель не найден"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True



def findTomorrow(bot,event):
    cm = re.match(r"^завтра$", event.text.lower())
    fio = bot.users[str(event.user_id)]["search"]
    prev = bot.users[str(event.user_id)]["last_msg"]
    pm = prev.lower() != "бот" and prev.lower() != "погода"
    if cm and pm:
      bot.users[str(event.user_id)]["search"] = ""
      if fio in bot.sch.teachers:
        text = bot.sch.teachers[fio].getSchedule(day=7)
      else:
        text = "Преподаватель не найден"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True


# print(sch.groups["ИКБО-18-22"].getWeeklySchedule())
# print(sch.groups["ИКБО-18-22"].getWeeklySchedule(nextWeek=True))
def findThisWeek(bot,event):
    cm = re.match(r"^на эту неделю$", event.text.lower())
    fio = bot.users[str(event.user_id)]["search"]
    prev = bot.users[str(event.user_id)]["last_msg"]
    pm = prev.lower() != "бот" and prev.lower() != "погода"
    if cm and pm:
      bot.users[str(event.user_id)]["search"] = ""
      if fio in bot.sch.teachers:
        text = bot.sch.teachers[fio].getWeeklySchedule()
      else:
        text = "Преподаватель не найден"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True
  

def findNextWeek(bot,event):
    cm = re.match(r"^на след. неделю$", event.text.lower())
    fio = bot.users[str(event.user_id)]["search"]
    prev = bot.users[str(event.user_id)]["last_msg"]
    pm = prev.lower() != "бот" and prev.lower() != "погода"
    if cm and pm:
      bot.users[str(event.user_id)]["search"] = ""
      if fio in bot.sch.teachers:
        text = bot.sch.teachers[fio].getWeeklySchedule(nextWeek=True)
      else:
        text = "Преподаватель не найден"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True

TEACHERS_HANDLERS = [findTeacher, findToday, findTomorrow, findThisWeek, findNextWeek]