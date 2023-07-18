class Valute:

  def __init__(
    self, 
    charcode: str, 
    amount: int, 
    fullname: str,
    pricerub: float
  ):
    self.code = charcode
    self.nominal = amount
    self.name = fullname
    self.value = pricerub
    

  # строковое представление аля JSON
  def __str__(self):
    return "{" + f"'code': '{self.code}', 'nominal': {self.nominal}, 'name': '{self.name}', 'value': {self.value}" + "}"

  # наименование с кодом
  def getName(self):
    return f"{self.code} - {self.name}"

  # курс единицы каждой валюты в рублях
  @property
  def ratio(self):
    return (self.value / self.nominal)


#############################################################################
#############################################################################
#############################################################################
class Exchanger:

  def __init__(self, date: str, valutes: dict):
    self.date = date
    self.valutes: dict = valutes
    self.mapping: dict = dict()
    for key in self.valutes.keys():
      mappingName = self.valutes[key].getName()
      self.mapping[mappingName] = key

  def __str__(self):
    return f"Valutes for {self.date}: " + ", ".join(self.valutes.keys())

  def convert(self, origin: str, target: str, amount: float):
    src = self.valutes[origin]
    tgt = self.valutes[target]
    return round((src.ratio * amount)/tgt.ratio,3)

  def getCodes(self):
    return list(self.valutes.keys())

  def __getitem__(self, index: int):
    keys = self.getCodes()
    return self.valutes[keys[index]]

  def getPrice(self, code):
    return self.valutes[code].value

  def code4Name(self, name: str):
    return self.mapping[name]

