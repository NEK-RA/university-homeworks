from random import randint
import re

import vk_api
from vk_api.longpoll import VkLongPoll, VkEventType
from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.utils import get_random_id


from mybackend.openweathermap import OWM
from mybackend.schedule import Schedule
from mybackend.utils import currentWeek

from bot.students import STUDENTS_HANDLERS
from bot.teachers import TEACHERS_HANDLERS
from bot.weather import WEATHER_HANDLERS

class VkBot:

  def __init__(self, bottoken, weathertoken):
    self.owm = OWM(weathertoken)
    self.session = vk_api.VkApi(token=bottoken)
    self.api = self.session.get_api()
    self.longpoll = VkLongPoll(self.session)
    self.users = {}
    self.sch = Schedule(debug=True)
    print("loading schedule")
    self.sch.load()

    kb = VkKeyboard(one_time=True)
    kb.add_button("Начать", color=VkKeyboardColor.POSITIVE)
    kb.add_button("Бот", color=VkKeyboardColor.POSITIVE)
    kb.add_line()
    kb.add_button("Найти", color=VkKeyboardColor.NEGATIVE)
    kb.add_button("Погода", color=VkKeyboardColor.POSITIVE)
    self.default = kb.get_keyboard()

    unknownKb = VkKeyboard(one_time=True)
    unknownKb.add_button("Начать")
    self.unknown = unknownKb.get_keyboard()


  def run(self):
    print("Running longpoll")
    for event in self.longpoll.listen():
      if event.type == VkEventType.MESSAGE_NEW and event.text:
        print("New from <{}>, text = <{}>".format(event.user_id, event.text))

        if str(event.user_id) not in self.users:
          self.users[str(event.user_id)] = {"group":"", "last_msg": "", "search":""}

        worked = False
        inner_handlers = [
          self.help,
          self.setGroup,
          self.whichWeek,
          self.whichGroup
        ]
        external_handlers = [
          *STUDENTS_HANDLERS,
          *TEACHERS_HANDLERS,
          *WEATHER_HANDLERS,
        ]
        for handler in inner_handlers:
          worked = handler(event)
          if worked == True:
            break

        if worked == None:
          for handler in external_handlers:
            worked = handler(self, event)
            if worked == True:
              break

        if worked == None:
          self.api.messages.send(
            user_id=event.user_id,
            random_id=get_random_id(),
            message="Неизвестная команда",
            keyboard=self.unknown
          )

        self.users[str(event.user_id)]["last_msg"] = event.text

        self.longpoll.update_longpoll_server()
        print("Event {} processed".format(event.message_id))



  def help(self, event):
    if re.match("^начать$", event.text.lower()):
      print("Запрошена инструкция")
      text = f"""
  Как пользоваться ботом:

Начать -> краткая инструкция
ИКБО-01-22 -> указать свою группу
Бот -> показать кнопки для выбора расписания
Бот понедельник -> показать расписание на понедельник (может быть другой день)
Бот вторник ИКБО-18-22 -> показать расписание на вторник для другой группы
Найти Иванов -> поиск преподавателя по фамилии
Погода -> показать текущую погоду
      """

      self.api.messages.send(
        user_id=event.user_id,
        random_id=get_random_id(),
        message=text,
        keyboard=self.default
      )

      return True



  def whichWeek(self,event):
    if re.match(r"^какая неделя$", event.text.lower()):
      self.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message=f"Идет {currentWeek()} неделя",
          keyboard=self.default
      )
      return True
    


  def whichGroup(self,event):
    if re.match(r"^какая группа$", event.text.lower()):
      self.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message="Ваша группа:"+self.users[str(event.user_id)]["group"] + "\nОтправьте мне наименование группы для изменения",
          keyboard=self.default
      )
      return True
    
    
  
  def setGroup(self, event):
    if re.match(r"^[а-я]{4}-\d{2}-\d{2}$", event.text.lower()):
      print("regex passed")
      uid = str(event.user_id)
      group = event.text.upper()
      if group in self.sch.groups:
        self.users[uid]["group"] = group
        if uid not in self.users.keys():
          text = "Я запомнил вашу группу"
        else:
          text = "Я изменил вашу группу"
      else:
        text = "Такой группы не найдено в расписании"  
      self.api.messages.send(
        user_id=event.user_id,
        random_id=get_random_id(),
        message=text,
        keyboard=self.default
      )
      return True
# конец