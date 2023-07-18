from datetime import date, timedelta
from back.parser import API

class GraphHelper:

  cache = dict()
  mapper = dict()

  @staticmethod
  def loadGraphPoints(valute, days):
    exchangers = None
    cacheKey = "|".join(days)
    if cacheKey in GraphHelper.cache.keys():
      exchangers = GraphHelper.cache[cacheKey]
    else:
      exchangers = list()
      for day in days:
        exchangers.append(API.buildExchanger(day))
      GraphHelper.cache[cacheKey] = exchangers
    valCode = exchangers[0].mapping[valute]
    return dict(x=[day.replace('/','\n') for day in days], y=[ex.getPrice(valCode) for ex in exchangers], nominal=exchangers[0].valutes[valCode].nominal)

  @staticmethod
  def getPeriods(periodType: str):
    if periodType == "неделя":
      return GraphHelper.getWeeks()
    elif periodType == "месяц":
      return GraphHelper.getMonths()
    elif periodType == "квартал":
      return GraphHelper.getQuarters()
    elif periodType == "год":
      return GraphHelper.getYears()

  @staticmethod
  def getWeeks():
    values = []
    moment = date.today()
    for i in range(4):
      values.append([(moment - timedelta(days=n)).strftime("%d/%m/%Y") for n in range(7)])
      moment = moment - timedelta(days=7)
    return values
    

  @staticmethod
  def getMonths():
    values = []
    moment = date.today()
    for i in range(4):
      values.append([(moment - timedelta(days=n)).strftime("%d/%m/%Y") for n in range(31) if n % 2 == 0 or n == 30])
      moment = moment - timedelta(days=31)
    return values

  @staticmethod
  def getQuarters():
    # квартал = 3 месяца
    values = []
    moment = date.today()
    for i in range(4):
      values.append([(moment - timedelta(days=n)).strftime("%d/%m/%Y") for n in range(93) if n % 6 == 0 or n == 92])
      moment = moment - timedelta(days=93)
    return values

  @staticmethod
  def getYears():
    values = []
    moment = date.today()
    for i in range(4):
      values.append([(moment - timedelta(days=n)).strftime("%d/%m/%Y") for n in range(366) if n % 24 == 0 or n == 365])
      moment = moment - timedelta(days=366)
    return values
