from discipline import Discipline
from academic import Academic
from practice import Practice
from plan import Plan
from utils import log

import pickle

dis: Discipline = None
acad: Academic = None
pract: Practice = None
plan: Plan = None

with open("task_d118/pickled.data","rb") as data:
  dis = pickle.load(data)
  acad = pickle.load(data)
  pract = pickle.load(data)
  plan = pickle.load(data)
  log("INF","Данные восстановлены с помощью pickle из другого скрипта")

print(dis)

print(acad)
acad.changeTest("экзамен")
acad.changeTutor("Новый преподаватель")

print(pract)
print(plan)
plan -= pract
print(plan)
del plan[0]
print(plan)