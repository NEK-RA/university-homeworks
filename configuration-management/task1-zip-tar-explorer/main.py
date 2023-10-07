# zipfile docs: https://docs.python.org/3/library/zipfile.html
# tarfile docs: https://docs.python.org/3/library/tarfile.html
import sys
import zipfile
import tarfile

IS_ZIP: bool = False
IS_TAR: bool = False
PWD: list[str] = []

############################################################


def pwd(noroot=False, customPWD=None):
  global PWD
  WD = customPWD.copy() if customPWD else PWD.copy()
  if len(WD) == 0:
    if noroot:
      return ""
    else:
      return "/"
  else:
    cwd = "/".join(WD)
    if noroot:
      return cwd
    else:
      return f"/{cwd}"


############################################################


def ls(archname, target):
  global IS_ZIP
  global IS_TAR
  global PWD
  names = []
  cwd = ""
  content = []

  # print("DEBUG: GOING WRONG FOR TAR!!!")

  if IS_ZIP:
    with zipfile.ZipFile(archname) as archive:
      content = archive.namelist()
  elif IS_TAR:
    with tarfile.TarFile(archname) as archive:
      content = archive.getnames()


  if target:
    target = target[:-1] if target.endswith("/") else target
    PWD_COPY = PWD.copy()
    parts = target.split("/")
    while len(parts) > 0:
      step = parts.pop(0)
      if step == "":  # due to split("/") the "/" will turn into ""
        PWD_COPY = []
      elif step == ".." and len(PWD_COPY) >= 1:
        PWD_COPY.pop()
      else:
        PWD_COPY.append(step)
    cwd = pwd(noroot=True, customPWD=PWD_COPY)
    valid = validateFolder(pwd(noroot=True, customPWD=PWD_COPY), archname)
    if not valid:
      return f"Путь {target} не существует. Проверьте доступные к переходу папки с помощью команды ls"
  else:
    cwd = pwd(noroot=True)

  # print(f"DEBUG: content for TAR: {content}")
  for name in content:
    if name.startswith(cwd):
      newname = name[len(cwd):]
      if newname.startswith("/"):
        newname = newname[1:]
      nnsplit = newname.split("/")
      newname = nnsplit[0] if len(nnsplit) == 1 else f"{nnsplit[0]}/"
      if newname and newname not in names:
        names.append(newname)
  return " ".join(sorted(names))


############################################################


def validateFolder(path, archname):
  content = []
  if IS_ZIP:
    with zipfile.ZipFile(archname) as archive:
      content = archive.namelist()
  elif IS_TAR:
    with tarfile.TarFile(archname) as archive:
      content = archive.getnames()
  return any(name.startswith(path) for name in content)


############################################################


def validateFile(path, archname):
  if path.endswith("/"):
    return False
  content = []
  if IS_ZIP:
    with zipfile.ZipFile(archname) as archive:
      content = archive.namelist()
  elif IS_TAR:
    with tarfile.TarFile(archname) as archive:
      content = archive.getnames()
  return any((name == path) for name in content)


############################################################


def cat(target, archname):
  global IS_ZIP
  global IS_TAR
  global PWD
  PWD_COPY = PWD.copy()
  parts = target.split("/")
  while len(parts) > 0:
    step = parts.pop(0)
    if step == "":  # due to split("/") the "/" will turn into ""
      PWD_COPY = []
    elif step == ".." and len(PWD_COPY) >= 1:
      PWD_COPY.pop()
    else:
      PWD_COPY.append(step)
  filepath = pwd(noroot=True, customPWD=PWD_COPY)
  valid = validateFile(filepath, archname)
  if not valid:
    return f"Файл по пути {target} не найден"
  if IS_ZIP:
    with zipfile.ZipFile(archname) as archive:
      with archive.open(filepath, "r") as file:
        return file.read().decode("utf-8")
  elif IS_TAR:
    with tarfile.TarFile(archname) as archive:
      with archive.extractfile(filepath) as file:
        return file.read().decode("utf-8")


############################################################


def cd(target, archname):
  global IS_ZIP
  global IS_TAR
  global PWD
  if target is None:
    PWD = []
  else:
    PWD_COPY = PWD.copy()
    parts = target.split("/")
    while len(parts) > 0:
      step = parts.pop(0)
      if step == "":  # due to split("/") the "/" will turn into ""
        PWD_COPY = []
      elif step == ".." and len(PWD_COPY) >= 1:
        PWD_COPY.pop()
      else:
        PWD_COPY.append(step)
    valid = validateFolder(pwd(noroot=True, customPWD=PWD_COPY), archname)
    if not valid:
      print(
          f"Путь {target} не существует. Проверьте доступные к переходу папки с помощью команды ls"
      )
    else:
      PWD = PWD_COPY.copy()


############################################################

if __name__ == "__main__":
  if len(sys.argv) < 2:
    print("Укажите Zip или Tar архив в качестве аргумента!")
    exit(1)
  arch = sys.argv[1]
  if arch.lower().endswith("zip") and zipfile.is_zipfile(arch):
    IS_ZIP = True
  elif arch.lower().endswith("tar") and tarfile.is_tarfile(arch):
    IS_TAR = True
  if not IS_ZIP and not IS_TAR:
    print(
        "Указанный первым аргументом файл должен иметь расширение 'zip' или 'tar'. Кроме того файл должен являться валидным Zip или Tar архивом."
    )
    exit(1)
  else:
    command = ""
    while command != "exit":
      command = input(f"{arch}:{pwd()} $ ")
      # help
      if command == "help":
        print("""
Доступные команды:
  help - Отобразить помощь по командам
  pwd - Отобразить текущее местонахождение. Не принимает аргументов.
  ls - Отображение списка файлов и папок. По умолчанию отображает в текущей папке, может принимать аргументом путь. Доступно ".." как ссылка на родительскую папку.
  cd - Переход в указанную папку. Доступно ".." как ссылка на родительскую папку. При отсутствии аргумента переходит в корень (путь: /).
  cat - Вывести содержимое файла. Принимает путь к файлу в качестве аргумента. Не принимает аргументов.
""".strip())
      # pwd
      if command == "pwd":
        print(pwd())

      # ls, ls /some/path
      if command.startswith("ls"):
        ls_args_start = command.find(" ")
        if ls_args_start == -1:
          print(ls(arch, None))
        else:
          dest = command[ls_args_start + 1:].strip()
          if dest:
            print(ls(arch, dest))
          else:
            print(ls(arch, None))

      # cd, cd /some/path/with/..
      if command.startswith("cd"):
        cd_args_start = command.find(" ")
        if cd_args_start == -1:
          cd(None, arch)
        else:
          dest = command[cd_args_start + 1:].strip()
          if dest:
            cd(dest, arch)
          else:
            cd(None, arch)

      # cat /some/path/../to/file
      if command.startswith("cat"):
        cat_args_start = command.find(" ")
        if cat_args_start == -1:
          print(
              "Для работы cat требуется аргумент - путь до какого-либо файла.")
        else:
          dest = command[cat_args_start + 1:].strip()
          if dest:
            print(cat(dest, arch))
          else:
            print(
                "Для работы cat требуется аргумент - путь до какого-либо файла."
            )
