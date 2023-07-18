from tkinter import Button, Label, StringVar
from tkinter.ttk import Notebook, Frame, Combobox, Radiobutton

import matplotlib
import matplotlib.pyplot as plt

from back.graph import GraphHelper
"""
– combobox для выбора валюты, combobox для выбора масштаба построения графика 
(неделя, месяц, квартал, год), combobox для выбора период (автоматически 
выбирается текущий период, присутствуют 3 предыдущих 
недели/месяца/квартала/года), кнопка для прорисовки графика, график.
"""
matplotlib.use("TkAgg")

class HistoryTab(Frame):

  def __init__(self, parent: Notebook):
    super().__init__(parent)

    # Управляющая часть
    topFrame = Frame(self)
    topFrame.pack(expand=False, side="top", fill="x")

    # Выбор валюты
    labelValute: Label = Label(topFrame, text="Валюта")
    labelValute.grid(row=0, column=0, pady=(15, 0), padx=15)

    self.tgtOptions: Combobox = Combobox(topFrame, state="readonly")
    self.tgtOptions["values"] = self.master.comboboxOptions
    self.tgtOptions.set(self.master.comboboxOptions[0])
    self.tgtOptions.grid(row=1, column=0, padx=15)

    # выбор периода
    self.periodType = StringVar()
    # Отслеживание изменения значений в конце, потому что иначе обработчик видит поля класса не полностью (только ту часть, что была инициализирована до указания обработчика)
    # self.periodType.trace_add(mode="write", callback=self._updatePeriodCombobox)
    self.periodType.set("неделя")

    labelPeriod: Label = Label(topFrame, text="Период")
    labelPeriod.grid(row=0, column=1, pady=(15, 0), padx=15)

    periodFrame: Frame = Frame(topFrame)
    periodFrame.grid(row=1, column=1)

    week: Radiobutton = Radiobutton(periodFrame,
                                    text="Неделя",
                                    variable=self.periodType,
                                    value="неделя")
    week.pack(side="left")

    month: Radiobutton = Radiobutton(periodFrame,
                                     text="Месяц",
                                     variable=self.periodType,
                                     value="месяц")
    month.pack(side="left")

    quarter: Radiobutton = Radiobutton(periodFrame,
                                       text="Квартал",
                                       variable=self.periodType,
                                       value="квартал")
    quarter.pack(side="left")

    year: Radiobutton = Radiobutton(periodFrame,
                                    text="Год",
                                    variable=self.periodType,
                                    value="год")
    year.pack(side="left")

    self.periodOptions = Combobox(topFrame, state="readonly")
    self.periodOptions.grid(row=2, column=1)

    # кнопка построения графика
    self.buildGraph: Button = Button(topFrame, text="Построить график")
    self.buildGraph.grid(row=3, column=0)
    self.buildGraph.configure(command=self.buildGraphic)

    self.statusLabel: Label = Label(topFrame, text="")
    self.statusLabel.grid(row=3, column=1)

    # Нижняя часть окна под график
    self.bottomFrame: Frame = Frame(self)
    self.bottomFrame.pack(expand=True, fill="both")

    # поле под график
    self.wdg = None

    # Отслеживание изменения значений в конце
    self.periodType.trace_add(mode="write",
                              callback=self._updatePeriodCombobox)
    self._updatePeriodCombobox()

  def _updatePeriodCombobox(self, *args):
    dates = GraphHelper.getPeriods(self.periodType.get())
    self.periods = dict()
    for period in dates:
      key = f"{period[0]} - {period[-1]}"
      self.periods[key] = period
    options = list(self.periods.keys())
    self.periodOptions["values"] = options
    self.periodOptions.set(options[0])

  def buildGraphic(self):
    periodKey = self.periodOptions.get()
    valute = self.tgtOptions.get()
    dates = self.periods[periodKey]
    try:
      points = GraphHelper.loadGraphPoints(valute, dates)
      self.statusLabel.configure(text="")
      if self.wdg:
        self.wdg.grid_forget()
      
      figure = plt.figure(figsize=(8,4))
      figure.subplots_adjust(left=0.1, right=0.95, bottom=0.2, top=0.95, wspace=0.4, hspace=0.4)
      canvas = matplotlib.backends.backend_tkagg.FigureCanvasTkAgg(figure, master=self.bottomFrame)
      self.wdg = canvas.get_tk_widget()
      figure.clear()
      plt.plot(points['x'][::-1], points['y'][::-1])
      plt.grid()
      plt.xlabel("Дата (число/месяц/год)")
      plt.ylabel(f"Цена (руб) за {points['nominal']} {valute[:3]}")
      self.wdg.grid(row=0, column=0, padx=20, pady=30)
    
    except KeyError:
      self.statusLabel.configure(text=f"График для \"{valute}\" на период \"{periodKey}\" не доступен.")

