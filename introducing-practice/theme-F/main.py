from os import getenv

from bot.bot import VkBot

TOKEN = getenv("BOT_TOKEN","")
OWM_KEY = getenv("OWM_KEY","")

if TOKEN and OWM_KEY:
  bot = VkBot(TOKEN, OWM_KEY)
  bot.run()
else:
  print("TOKEN WAS NOT SET")

# from mybackend.schedule import Schedule

# sch = Schedule(debug=True)
# sch.load()
# for key in sch.teachers.keys():
#   print(key)
# print(sch.rawTeachers("Красников"))

# from mybackend.openweathermap import OWM
# owm = OWM(key=OWM_KEY)
# print(owm.getCurrent())
# print(owm.get5Days())