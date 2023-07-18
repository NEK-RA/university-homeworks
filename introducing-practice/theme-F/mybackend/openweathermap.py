import json
from requests import get
import requests

from mybackend.utils import *

# https://openweathermap.org/current
# https://openweathermap.org/forecast5


class OWM:
  def __init__(self, key):
    self.api = key
    self.now = "https://api.openweathermap.org/data/2.5/weather?q=moscow&units=metric&lang=ru&appid="
    self.days5hours3 = "https://api.openweathermap.org/data/2.5/forecast?q=moscow&units=metric&lang=ru&appid="
    self.iconUrl = "https://openweathermap.org/img/wn/{}@2x.png"

  def getCurrent(self, src=None):
    data = requests.get(self.now + self.api).json() if src == None else src
    summary = data["weather"][0]["main"]
    description = data["weather"][0]["description"]
    mint = data["main"]["temp_min"]
    maxt = data["main"]["temp_max"]
    temp = f"{mint} - {maxt}" if mint != maxt else maxt
    pressure = round(data["main"]["pressure"] / 1.33, 2)
    humidity = data["main"]["humidity"]
    windspd = data["wind"]["speed"]
    windirdeg = data["wind"]["deg"]

    if windirdeg < 20 and windirdeg >=0 or windirdeg < 359 and windirdeg >=340:
      windir = "северный"
    elif windirdeg >=20 and windirdeg < 60:
      windir = "северо-восточный"
    elif windirdeg >=60 and windirdeg < 110:
      windir = "восточный"
    elif windirdeg >=110 and windirdeg < 160:
      windir = "юго-восточный"
    elif windirdeg >=160 and windirdeg < 200:
      windir = "южный"
    elif windirdeg >=200 and windirdeg < 250:
      windir = "юго-западный"
    elif windirdeg >=250 and windirdeg < 290:
      windir = "западный"
    elif windirdeg >=290 and windirdeg < 340:
      windir = "северо-западный"
                        
    result = (f"Подгода в Москве: {summary}\n" if src == None else "") +\
    f"{description}, температура: {temp}°С\n"+\
    f"Давление: {pressure} мм рт. ст., влажность: {humidity} %\n"+\
    f"Ветер: {'сильный' if windspd > 6 else 'слабый'}, {windspd} м/с, {windir}\n"
    return dict(text=result, icon=data["weather"][0]["icon"])

  def getToday(self, needTomorrow=False):
    data = requests.get(self.days5hours3 + self.api).json()
    dayparts = []
    daypartNames = {"0": "Ночь", "6": "Утро", "12": "День", "18": "Вечер"}
    today = getToday().day
    tomorrow = getTomorrow().day
    if needTomorrow:
      today = todayPlus(1).day
      tomorrow = todayPlus(2).day
    for part in data["list"]:
      partTime = t2date(part["dt"])
      mde = partTime.hour in [6, 12, 18]
      if (today == partTime.day and mde) or (tomorrow == partTime.day and partTime.hour == 0):
        part["dt"] = partTime
        dayparts.append(part)
    icons = []
    result = f"Погода в Москве {('завтра' if needTomorrow else'сегодня')}:\n"
    for part in dayparts:
      data = self.getCurrent(src=part)
      result += "\n" + daypartNames[str(part["dt"].hour)] + "\n"
      result += data["text"] + "\n"
      icons.append(data["icon"])
    return dict(images=icons, text=result)
    


  def get5Days(self):
    data = requests.get(self.days5hours3 + self.api).json()
    dayparts = []
    for part in data["list"]:
      partTime = t2date(part["dt"])
      dn = partTime.hour in [0, 12]
      if dn:
        part["dt"] = partTime
        dayparts.append(part)
    dayicons = []
    nighticons = []
    result = f"Погода в Моксве с {dayparts[0]['dt'].strftime('%d.%m')} по {dayparts[-1]['dt'].strftime('%d.%m')}:\n"
    result += "// "
    for part in dayparts:
      if part["dt"].hour == 12:
        result += str(part["main"]["temp"]) + "°С // "
        dayicons.append(part["weather"][0]["icon"])
    result += "\n// "
    for part in dayparts:
      if part["dt"].hour == 0:
        result += str(part["main"]["temp"]) + "°С // "
        nighticons.append(part["weather"][0]["icon"])
    result += "\n"
    return dict(text=result, day=dayicons, night=nighticons)

         

###