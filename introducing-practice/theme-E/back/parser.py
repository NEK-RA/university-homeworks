# http://www.cbr.ru/scripts/XML_daily.asp?date_req=22/04/2022
from datetime import datetime
import xml.etree.ElementTree as xmltree

from requests import get

from back.responses import Response, ResponseOk, ResponseBad
from back.exchanger import Valute, Exchanger

class API:

  @staticmethod
  def getTodayRatio():
    today = datetime.now().date().strftime("%d/%m/%Y")
    return API.buildExchanger(today)


    
  @staticmethod
  def _validateDate(date: str) -> bool:
    if len(date) != 10:
      return False
    try:
      datetime.strptime(date, "%d/%m/%Y")
      return True
    except ValueError:
      return False
  
  @staticmethod
  def _fetchXmlAt(date: str) -> str:
    
    isValid = API._validateDate(date)
    if not isValid:
      return ResponseBad(
        "Запрошена некорректная дата. Необходимый формат: дд/мм/гггг (10 символов)"
      )
    url: str = f"http://www.cbr.ru/scripts/XML_daily.asp?date_req={date}"
    result = get(url)
    if result.status_code == 200:
      return ResponseOk(result.text)
    else:
      return ResponseBad(
        f"Received result {result.reason} (HTTP code {result.headers['status']}). Content:\n{result}"
      )
  
  

  @staticmethod
  def buildExchanger(date: str) -> Exchanger:
    xml: Response = API._fetchXmlAt(date)
    if isinstance(xml, ResponseBad):
      return None
    elif isinstance(xml, ResponseOk):
      valutes: dict(Valute) = dict()
  
      tree = xmltree.fromstring(xml.data)
      for valxml in tree.findall("Valute"):
        val = Valute(charcode=valxml.find("CharCode").text,
                     amount=int(valxml.find("Nominal").text),
                     fullname=valxml.find("Name").text,
                     pricerub=float(valxml.find("Value").text.replace(",", ".")))
        valutes[val.code] = val
  
      rub: Valute = Valute(charcode="RUB",
                           amount=1,
                           fullname="Российский рубль",
                           pricerub=1)
      valutes[rub.code] = rub
  
      # Exchanger
      return Exchanger(date=date,valutes=valutes)
  
