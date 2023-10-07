from re import match
from sys import exit, stderr
from requests import get

###########################################################################


def simplifyDeps(deps):
  # print(f"DEBUG: simplifyDeps: raw result {deps}")
  simpler = set()
  if deps is not None:
    for dep in deps:
      regex = match(r'[A-Za-z]+[A-Za-z0-9_.\-]*', dep)
      if regex is not None:
        simpler.add(regex.group())
      else:
        simpler.add(dep)
  # print(f"DEBUG: simplifyDeps: final result {simpler}")
  return list(simpler)


###########################################################################

DEPS_CACHE = dict()

def getDeps(pkg):
  global DEPS_CACHE
  if(pkg in DEPS_CACHE.keys()):
    print(f"WARNING: Пакет {pkg} найден в кэше, пропуск", file=stderr)
    return simplifyDeps(DEPS_CACHE[pkg])
  else:
  # print(f"DEBUG: getDeps: requesting deps for {pkg}")
    response = get(f"https://pypi.org/pypi/{pkg}/json")
    if response.status_code == 200:
      data = response.json()
      # print(f"WARNING: Пакет {pkg} зависит от: " + str(data['info']['requires_dist']), file=stderr)
      DEPS_CACHE[pkg] = data['info']['requires_dist']
      return simplifyDeps(DEPS_CACHE[pkg])
    elif response.status_code == 404:
      print(f"WARNING: Пакет {pkg} не найден в pypi", file=stderr)
      return list()
    else:
      print(f"ERROR: Произошла непредвиденная ошибка при запросе данных для пакета {pkg}: {response.status_code} {response.headers['status']}", file=stderr)
      return list()


###########################################################################


class Node:

  PKG_NAME = r"[A-Za-z]+[A-Za-z0-9_.\-]*"

  def __init__(self, name, parent, depth):
    self.name = name
    self.parent = parent
    self.level = 0
    self.deps = []

    if parent is not None:
      self.level = parent.level + 1
      parent.deps.append(self)

    if self.level < depth:
      print(f"\n\nDEBUG: Node: __init__: getting dependencies for {self.name}", file=stderr)
      deps = getDeps(self.name)
      for dep in deps:
        Node(dep, self, depth)

  def __str__(self):
    return self.name

  def graphviz(self):
    result = ""
    for dep in self.deps:
      result += f"\"{self.name}\" -> \"{dep.name}\"\n"
    for dep in self.deps:
      result += dep.graphviz()
    if self.parent is None:
      return "digraph{\n" + result + "}"
    else:
      return result


###########################################################################

def clean(raw):
  data = raw.split("\n")
  result = list()
  for line in data:
    if line.strip() not in result:
      result.append(line)
  # print(len(data), len(result), file=stderr)
  return "\n".join(result)
  

###########################################################################

if __name__ == "__main__":

  print("Укажите имя пакета:", end=" ", file=stderr)
  package = input()
  if (match(Node.PKG_NAME, package)):
    print("Глубина сканирования:", end=" ", file=stderr)
    depth = int(input())
    depth = depth if depth >= 1 else 1
    root = Node(package, None, depth)
    print(clean(root.graphviz()))
  else:
    print("Некорректное наименование пакета", file=stderr)
