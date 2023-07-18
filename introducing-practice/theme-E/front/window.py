from tkinter import Tk
from tkinter.ttk import Notebook

from front.exchangetab import ExchangerTab
from front.historytab import HistoryTab
from front.abouttab import AboutTab

class MainWindow(Tk):
  def __init__(self):
    super().__init__()
    self.title("Обменник и динамика курсов")
    self.resizable(width=True, height=True)

    self.comboboxOptions = []
    
    self.tabs = Notebook(self)
    exchanger = ExchangerTab(self.tabs)
    graph = HistoryTab(self.tabs)
    about = AboutTab(self.tabs)
    self.tabs.add(exchanger, text="Обменник")
    self.tabs.add(graph, text="Динамика курса")
    self.tabs.add(about, text="О программе")
    self.tabs.pack(expand=True, fill="both")

    self.tabs.bind("<<NotebookTabChanged>>", self.tabChanged)


  def tabChanged(self, event):
    tabName = self.tabs.tab(self.tabs.select())['text']
    if tabName == "Динамика курса":
      self.geometry("840x600")
    else:
      self.geometry("400x230")
