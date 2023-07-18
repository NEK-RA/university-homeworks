import re

from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.utils import get_random_id

def botRasp(bot,event):
    if re.match("^бот$", event.text.lower()):
      if bot.users[str(event.user_id)]["group"] != "":
        text = "Показать расписание ..."
        kb = VkKeyboard(one_time=True)
        kb.add_button("Сегодня", color=VkKeyboardColor.POSITIVE)
        kb.add_button("Завтра")
        kb.add_line()
        kb.add_button("На эту неделю", color=VkKeyboardColor.POSITIVE)
        kb.add_button("На след. неделю")
        kb.add_line()
        kb.add_button("Какая неделя")
        kb.add_button("Какая группа")

        bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message=text,
          keyboard=kb.get_keyboard()
        )
        return True
      else:
        bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message="Вы еще не указали свою группу",
          keyboard=bot.unknown
        )
        return True
      
# print(sch.groups["ИКБО-18-22"].scheduleForDay("среда"))

def getRaspForDay(bot,event):
    args = event.text.lower().split(" ")
    days = ["понедельник", "вторник", "среда", "четверг", "пятница", "суббота"]
    if args[0] == "бот":
      if args[1] in days:
        if len(args) == 2:
          grp = bot.users[str(event.user_id)]["group"]
          if grp != bot.sch.groups:
            text = bot.sch.groups[grp].scheduleForDay(args[1])
          else:
            text = "Ваша группа не найдена в расписании"
        elif len(args) == 3:
          grp = args[2].upper()
          if grp in bot.sch.groups:
            text = bot.sch.groups[grp].scheduleForDay(args[1])
          else:
            text = "Указанная группа не найдена в расписании"
        else:
          text = "Неизвестные аргументы команды"
      else:
        text = f"{args[1]} не соответствует ни одному дню из списка: {', '.join(days)}"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True


# print(sch.groups["ИКБО-18-22"].getSchedule(day=0))
# print(sch.groups["ИКБО-18-22"].getSchedule(day=7))
  
def getRaspToday(bot,event):
    cm = re.match(r"^сегодня$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "бот"
    if cm and pm:
      grp = bot.users[str(event.user_id)]["group"]
      if grp in bot.sch.groups:
        text = bot.sch.groups[grp].getSchedule(day=0)
      else:
        text = "Вашей группы не обнаружено в расписании"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True

  

def getRaspTomorrow(bot,event):
    cm = re.match(r"^завтра$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "бот"
    if cm and pm:
      grp = bot.users[str(event.user_id)]["group"]
      if grp in bot.sch.groups:
        text = bot.sch.groups[grp].getSchedule(day=7)
      else:
        text = "Вашей группы не обнаружено в расписании"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True


# print(sch.groups["ИКБО-18-22"].getWeeklySchedule())
# print(sch.groups["ИКБО-18-22"].getWeeklySchedule(nextWeek=True))
def getRaspThisWeek(bot,event):
    cm = re.match(r"^на эту неделю$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "бот"
    if cm and pm:
      grp = bot.users[str(event.user_id)]["group"]
      if grp in bot.sch.groups:
        text = bot.sch.groups[grp].getWeeklySchedule()
      else:
        text = "Вашей группы не обнаружено в расписании"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True
  

def getRaspNextWeek(bot,event):
    cm = re.match(r"^на след. неделю$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "бот"
    if cm and pm:
      grp = bot.users[str(event.user_id)]["group"]
      if grp in bot.sch.groups:
        text = bot.sch.groups[grp].getWeeklySchedule(nextWeek=True)
      else:
        text = "Вашей группы не обнаружено в расписании"
      bot.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message=text,
            keyboard=bot.default
      )
      return True

STUDENTS_HANDLERS = [botRasp, getRaspForDay, getRaspToday, getRaspTomorrow, getRaspThisWeek, getRaspNextWeek]