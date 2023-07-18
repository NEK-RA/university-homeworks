from tkinter import Label, Button
from tkinter.ttk import Notebook, Frame

from datetime import datetime
import webbrowser

class AboutTab(Frame):

  def __init__(self, parent: Notebook):
    super().__init__(parent)
    devName: Label = Label(self, text="Разработчик: Налецкий Евгений")
    devGroup: Label = Label(self, text="Группа: ИКБО-18-22")
    devDiscipline: Label = Label(
      self,
      text=
      "Разработано при прохождении дисциплины:\nОзнакомительная практика, Тема E"
    )
    valutesSource: Label = Label(self, text="Курсы валют загружаются с сайта ЦБ РФ")

    devName.grid(row=0, ipadx=50, ipady=5)
    devGroup.grid(row=1, ipadx=50, ipady=5)
    devDiscipline.grid(row=2, ipadx=50, ipady=5)
    valutesSource.grid(row=3, ipadx=50, ipady=5)

    cbrfButton: Button = Button(self, text="Курсы на сегодня (XML)", command=self.openCBRF)
    cbrfButton.grid(row=4, ipadx=50, ipady=5)

  def openCBRF(self):
    webbrowser.open("http://www.cbr.ru/scripts/XML_daily.asp?date_req="+datetime.now().date().strftime("%d/%m/%Y"))
