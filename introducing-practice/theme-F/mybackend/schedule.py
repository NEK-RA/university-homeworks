from pathlib import Path
from random import randint
import hashlib
import pickle

from mybackend.api import API
from mybackend.book import Book
from mybackend.group import Group
from mybackend.teacher import Teacher

class Schedule:
  def __init__(self, debug=False):
    self.debug = debug
    self.folder = Path("data")
    self.debugDump = self.folder.joinpath("cached.pickle")
    self.tmpfolder = None
    self.names = {"first":"iit1.xlsx", "second":"iit2.xlsx", "third":"iit3.xlsx"}
    self.iit = dict()
    self.groups = dict()
    self.teachers = dict()

#######################################################################################################################################

  def download(self):
    randPref = "".join([chr(randint(ord("a"),ord("z"))) for i in range(10)])
    self.tmpfolder = self.folder.joinpath(randPref + "-temp")
    API.downloadScheduleTo(self.tmpfolder.as_posix())

#######################################################################################################################################

  def useNew(self):
    for file in self.tmpfolder.iterdir():
      if "1-kurs" in file.name:
        file.rename(self.folder.joinpath(self.names["first"]))
      elif "2-kurs" in file.name:
        file.rename(self.folder.joinpath(self.names["second"]))
      elif "3-kurs" in file.name:
        file.rename(self.folder.joinpath(self.names["third"]))
    self.tmpfolder.rmdir()
    self.tmpfolder = None

#######################################################################################################################################

  def load(self):
    loaded = False
    if self.debug:
      if self.debugDump.exists():
        print("Debug dump found, reading")
        with open(self.debugDump,"rb") as dump:
          self.iit = pickle.load(dump)
          print("Debug dump loaded")
          loaded = True
      else:
        print("Debug arg was passed but debug pickle dump was not found")
    
    if not loaded:
      self.iit = dict()
      for key in self.names.keys():
        if not self.folder.joinpath(self.names[key]).exists():
          self.download()
          self.useNew()
          break
      
      for key in self.names.keys():
        self.iit[key] = Book(self.folder.joinpath(self.names[key]).as_posix())
        print(self.names[key],"loaded")
      
      if self.debug:
        with open(self.debugDump, "wb") as dump:
          pickle.dump(self.iit, dump)
        print("Debug dump saved after loading data")
    
    self.groups = dict()
    for key in self.iit:
      book = self.iit[key]
      for i in range(1,book.cols, 15):
        # Студенческие группы
        gr1 = book.sheet.cell(row=2, column=i+5).value
        if gr1 != None and gr1 != "":
          self.groups[gr1] = Group(name=gr1, book=book, row=2, col=i+5)
        gr2 = book.sheet.cell(row=2, column=i+10).value
        if gr2 != None and gr2 != "":
          self.groups[gr2] = Group(name=gr2, book=book, row=2, col=i+10)
        
        # преподаватели
        for j in range(4, 88):
          t1 = str(book.sheet.cell(row=j, column=i+5+2).value).strip()
          t2 = str(book.sheet.cell(row=j, column=i+10+2).value).strip()
          if t1:
            t1 = t1.replace(",1 п/г","").replace("(1 п/г","").replace(",2 п/г","").replace("\n\n",",")
            t1sep = t1.split(",")
            for t1s in t1sep:
              if t1s != "":
                if t1s not in self.teachers.keys():
                  self.teachers[t1s] = Teacher(name=t1s, book=book)
                self.teachers[t1s].count({"row":j,"column":i+5+2})
          if t2:
            t2 = t2.replace(",1 п/г","").replace("(1 п/г","").replace(",2 п/г","").replace("\n\n",",")
            t2sep = t2.split(",")
            for t2s in t2sep:
              if t2s != "": 
                if t2s not in self.teachers.keys():
                  self.teachers[t2s] = Teacher(name=t2s, book=book)
                self.teachers[t2s].count({"row":j,"column":i+10+2})
            continue
      print("Loaded all groups and teachers from",key,"book")

#######################################################################################################################################

  def update(self):
    hasher = hashlib.new("md5")
    hashes = []
    for key in self.names:
      with open(self.folder.joinpath(self.names[key]), "rb") as existing:
        ex = existing.read()
        hasher.update(ex)
        hashes.append(hasher.hexdigest())
    
    self.download()
    for key in self.names:
      with open(self.folder.joinpath(self.names[key]), "rb") as existing:
        ex = existing.read()
        hasher.update(ex)
        hashes.append(hasher.hexdigest())

    needUpd = False
    for file in self.tmpfolder.iterdir():
      with open(file, "rb") as new:
        nw = new.read()
        hasher.update(ex)
        if hasher.hexdigest() in hashes:
          continue
        else:
          needUpd = True
    
    if needUpd:
      self.useNew()
      self.load()

#######################################################################################################################################

  def rawTeachers(self, surname):
    return [key for key in self.teachers.keys() if surname.lower() in key.lower()]
