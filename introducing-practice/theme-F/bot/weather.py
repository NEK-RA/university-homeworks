import re

import requests
import PIL.Image as Image

from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.utils import get_random_id
from vk_api import VkUpload


def uploadWeatherIcon(bot, iconList, savePath):
    uploader = VkUpload(bot.session)
    icons = []
    for icon in iconList:
        image = requests.get(bot.owm.iconUrl.format(icon), stream=True)
        icons.append(image)
    
    if len(icons) == 1:
        photo = uploader.photo_messages(photos=icons[0].raw)[0]
        return "photo{}_{}".format(photo["owner_id"], photo["id"])
    else:
        savePath = f"{savePath}-forecast.png"
        img = Image.new("RGBA", (len(icons)*100, 100))
        for i,icon in enumerate(icons):
            next = Image.open(icon.raw)
            img.paste(next, (100*i, 0, 100*(i+1),100))
        img = img.save(savePath, format="PNG")
        photo = uploader.photo_messages(savePath)[0]
        return "photo{}_{}".format(photo["owner_id"], photo["id"])


def getWeatherMenu(bot, event):
    if re.match(r"^погода$", event.text.lower()):
      kb = VkKeyboard(one_time=True)
      kb.add_button("Сейчас", color=VkKeyboardColor.POSITIVE)
      kb.add_button("Сегодня")
      kb.add_button("Завтра")
      kb.add_line()
      kb.add_button("На 5 дней")

      bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message="Показать погоду в Москве",
          keyboard=kb.get_keyboard()
      )
      return True
  


def getCurrentWeather(bot,event):
    cm = re.match(r"^сейчас$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "погода"
    if cm and pm:
      cast = bot.owm.getCurrent()
      attach = uploadWeatherIcon(bot, [cast["icon"]], event.user_id)
      bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message=cast["text"],
          attachment=attach,
          keyboard=bot.default
      )
      return True



def getTodayWeather(bot,event):
    cm = re.match(r"^сегодня$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "погода"
    if cm and pm:
      cast = bot.owm.getToday()
      attach = uploadWeatherIcon(bot, cast["images"], event.user_id)
      bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          message=cast["text"],
          attachment=attach,
          keyboard=bot.default
      )
      return True



def getTomorrowWeather(bot,event):
    cm = re.match(r"^завтра$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "погода"
    if cm and pm:
      cast = bot.owm.getToday(needTomorrow=True)
      attach = uploadWeatherIcon(bot, cast["images"], event.user_id)
      bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          attachment=attach,
          message=cast["text"],
          keyboard=bot.default
      )
      return True
    


def get5DaysWeather(bot,event):
    cm = re.match(r"^на 5 дней$", event.text.lower())
    pm = bot.users[str(event.user_id)]["last_msg"].lower() == "погода"
    if cm and pm:
      cast = bot.owm.get5Days()
      attach = uploadWeatherIcon(bot, cast["day"], event.user_id)
      bot.api.messages.send(
          user_id=event.user_id,
          random_id=get_random_id(),
          attachment=attach,
          message=cast["text"],
          keyboard=bot.default
      )
      return True
    

WEATHER_HANDLERS = [getWeatherMenu, getCurrentWeather, getTodayWeather, getTomorrowWeather, get5DaysWeather]