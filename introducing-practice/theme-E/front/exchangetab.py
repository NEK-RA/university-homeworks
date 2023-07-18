from tkinter import Label, Entry, Button, StringVar, IntVar, LEFT
from tkinter.ttk import Notebook, Frame, Combobox

from back.parser import API
from back.exchanger import Exchanger

class ExchangerTab(Frame):

  def __init__(self, parent: Notebook):
    super().__init__(parent)

    self.ratios = None

    self.src = StringVar()
    self.tgt = StringVar()
    self.amount = IntVar()
    self.result = StringVar()

    # первый список
    srcLabel = Label(self, text="Конвертируем из:", justify=LEFT)
    srcLabel.grid(row=0, column=0, padx=15, pady=(15, 0))

    self.srcValutes = Combobox(self, state="readonly", textvariable=self.src)
    self.srcValutes.grid(row=1, column=0, padx=15)

    # второй список
    tgtLabel = Label(self, text="Конвертируем в:", justify=LEFT)
    tgtLabel.grid(row=2, column=0, padx=15, pady=(15, 0))

    self.tgtValutes = Combobox(self, state="readonly", textvariable=self.tgt)
    self.tgtValutes.grid(row=3, column=0, padx=15)

    # текстовый ввод
    entryLabel = Label(self, text="Кол-во валюты")
    entryLabel.grid(row=0, column=1, padx=15, pady=(15, 0))

    self.field = Entry(self)
    self.field.insert(0,"1")
    self.field.grid(row=1, column=1, padx=15)

    # кнопка конвертации
    self.resultLabel = Label(self, text="Загружаем курсы обмена")
    self.resultLabel.grid(row=2, column=1, padx=15, pady=(15, 0))

    self.convertButton = Button(self, text="Конвертировать", state="disabled", command=self.convert)
    self.convertButton.grid(row=3, column=1, padx=15)
    
    self.loadExchanger()

    
  def loadExchanger(self):
    self.ratios: Exchanger = API.getTodayRatio()

    names = sorted(list(self.ratios.mapping.keys()))
    self.master.comboboxOptions = sorted(list(self.ratios.mapping.keys()))

    self.srcValutes["values"] = names
    self.srcValutes.set(names[0])
    
    self.tgtValutes["values"] = names
    self.tgtValutes.set(names[-1])
    
    self.convertButton["state"]="active"
    self.resultLabel.configure(text="Курсы обмена загружены")

  def convert(self):
    src = self.ratios.code4Name(self.srcValutes.get())
    tgt = self.ratios.code4Name(self.tgtValutes.get())
    
    amount = float(self.field.get().replace(",","."))
    result = round(self.ratios.convert(src,tgt,amount),2)
    
    self.resultLabel.configure(
      text = f"{amount} {src} = {result} {tgt}"
    )