from pathlib import Path
from queue import Queue
from subprocess import run, PIPE, CompletedProcess
from time import time

def printFunctions(path):
  with open(path,"r",encoding="utf8") as src:
    code: str = src.read().split("\n")
    for line in code:
      if line.startswith("def"):
        print(f'>>>> >>>> function "{line[4:-1]}"')





def execute(path:str,input:str,encoding="utf8"):
  out: CompletedProcess = run(f"python \"{path}\"", shell=True, text=True, input=input, capture_output=True, encoding=encoding)
  return out.stdout or out.stderr





def sortFiles(root: Path):
  # Целевая папка
  maindir: Path = root.joinpath("Ознакомительная папка")
  if not maindir.exists():
    maindir.mkdir()
    print(f"Основная папка ({maindir}) создана")
  else:
    print(f"Обнаружена папка {maindir.name}")

  # Создание подпапок
  topicA: Path = maindir.joinpath("Тема A")
  topicB: Path = maindir.joinpath("Тема B")
  for subdir in (topicA, topicB):
    if not subdir.exists():
      subdir.mkdir()
      print(f"Создана папка {subdir}")
    else:
      print(f"Обнаружена папка {subdir.name}")

  # Перемещение
  files: list[Path] = list(root.iterdir())
  files = [file for file in files if file.name.startswith("task_")]

  for file in files:    
    destination: str = ""
    if file.name.startswith("task_A") or file.name.startswith("task_a"):
      destination = topicA.absolute().as_posix()+"/"+file.name
    elif file.name.startswith("task_B") or file.name.startswith("task_b"):
      destination = topicB.absolute().as_posix()+"/"+file.name
    
    file.rename(destination)
  print("\n\n")
  return maindir





def walkNrun(root: Path):
  start = root.joinpath("Ознакомительная папка")
  if start.exists():
    textfile:str = ""
    # Составление списка файлов для выполнения
    walkthrough: Queue[Path] = Queue()
    walkthrough.put(start)
    scripts: list[Path] = []

    while not walkthrough.empty():
      parent = walkthrough.get()
      if parent.is_dir():
        for child in parent.iterdir():
          walkthrough.put(child)
      elif parent.is_file() and parent.name.endswith(".py"):
        scripts.append(parent)
      elif parent.is_file() and parent.name.endswith(".txt"):
        textfile = parent.resolve().as_posix()


    print("Файл для задания B4:", textfile)
    print("Обнаруженные скрипты:")

    lastParent = None
    for script in sorted(scripts):
      # Имя папки
      if script.parent.name != lastParent:
        print(f'\n\nfolder "{script.parent.name}"')
        lastParent = script.parent.name

      # Имя скрипта
      print(f'\n>>>> script "{script.name}"')
      
      # Имена функций
      printFunctions(script.as_posix())

      # Запуск и время
      launched = time()
      if script.name.startswith("task_B4"):
        output = execute(path=script.as_posix(), input=textfile, encoding="utf8")
      else:
        output = execute(path=script.as_posix(), input="0", encoding="utf8")
      timer = round(time() - launched,3)

      print(f'>>>> >>>> output "{output.strip()}"')
      print(f'>>>> >>>> time "{timer}" sec')





# Т.к. текущая рабочая папка будет папка с Темой D, а задание в подпапке
cwd: Path = Path.cwd().joinpath("task_d418")
print("Работаем в папке:",cwd)
sortFiles(cwd)
walkNrun(cwd)