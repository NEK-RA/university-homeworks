"""
Создать txt-файл, вставить туда любую англоязычную статью из Википедии.
Реализовать одну функцию, которая выполняет следующие операции:
- прочитать файл построчно;
- непустые строки добавить в список;
- удалить из каждой строки все цифры, знаки препинания, скобки, кавычки и т.д. (остаются латинские буквы и пробелы);
- объединить все строки из списка в одну, используя метод join и пробел, как разделитель;
- создать словарь вида {“слово”: количество, “слово”: количество, … } для подсчета количества разных слов,
  где ключом будет уникальное слово, а значением - количество;
- вывести в порядке убывания 10 наиболее популярных слов, используя форматирование
  (вывод примерно следующего вида: “ 1 place --- sun --- 15 times \n....”);
- заменить все эти слова в строке на слово “PYTHON”;
- создать новый txt-файл;
- записать строку в файл, разбивая на строки, при этом на каждой строке записывать не более 100 символов
  при этом не делить слова.
"""

def whitelisted(char):
  space = char == " "
  small = ord(char) >= ord("a") and ord(char) <= ord("z")
  big = ord(char) >= ord("A") and ord(char) <= ord("Z")
  return space or small or big


def wiki_function():
    # Тело функции
    filename = input("Введите название файла: ")
    # Запись непустых строк
    not_empty = []
    with open(filename,"r") as file:
      for line in file.readlines():
        if len(line.strip()) != 0:
          not_empty.append(line)
    print("Всего ", len(not_empty), " непустых строк")

    # Удаление лишних символов
    blacklist = set()
    for i in range(len(not_empty)):
      for c in not_empty[i]:
        if not whitelisted(c):
          blacklist.add(c)
      for bad in blacklist:
        not_empty[i] = not_empty[i].replace(bad,"")
    
    # Объединение в текст
    text = " ".join(not_empty)
    text = text.strip()

    # Словарь для подсчета слов
    freq = dict()
    for word in text.split(" "):
      if word in freq.keys() and word != "":
        freq[word] += 1
      else:
        freq[word] = 1
    print(len(freq.keys()), " уникальных слов")

    # Поиск топов
    # Найдем минимум чтобы отталкиваться от него в поиске максимума
    minword = list(freq.keys())[0]
    mincnt = freq[minword]
    for key in freq.keys():
      if freq[key] < mincnt:
        mincnt = freq[key]
        minword = key

    # Поиск наиболее частого чтобы обозначить верхнюю границу
    top10 = []
    maxcnt = mincnt
    maxword = minword
    for key in freq.keys():
      if freq[key] > maxcnt:
        maxcnt = freq[key]
        maxword = key
    top10.append(maxword)
    topword = maxword
    
    # Поиск остальных 9 слов
    for i in range(9):
      maxword = minword
      maxcnt = mincnt

      for key in freq.keys():
        if freq[key] > maxcnt\
          and freq[key] <= freq[topword]\
          and key not in top10:
            maxcnt = freq[key]
            maxword = key
      top10.append(maxword)
      topword = maxword
    
    # Сортировка частых слов
    top10 = sorted(top10, key = lambda d: freq[d], reverse = True)
    counter = 1
    for word in top10:
      print(f"{counter} place --- {word} --- {freq[word]} times")
      counter += 1
    popularsum = sum([freq[word] for word in top10])
    print(f"В сумме самые популярные слова встретились {popularsum} раз")

    # Заменить все эти слова в тексте на “PYTHON”
    for word in top10:
      text = text.replace(word,"PYTHON")

    # Cоздать новый txt-файл;
    # Запись текста в файл, разбивая на строки, при этом на каждой строке записывать не более 100 символов, при этом не делить слова.
    with open(f"{filename}.edited.txt","w") as final:
      line = ""
      endline = False
      for word in text.split(" "):
        if word == "":
          continue

        if endline:
          # print("yet another line has length",len(line))
          line = line.strip()
          line += "\n"
          final.write(line)
          line = ""
          endline = False

        nextwordlen = len(line) + len(word)
        if nextwordlen <= 100:
          line += word
        else:
          endline = True
          continue

        nextspacelen = len(line) + 1
        if nextspacelen <= 100:
          line += " "
        else:
          endline = True
          continue

    return 1


# Вызов функции
wiki_function()