import re

test_strings = [
  dict(
    src="Нужен ответ на письмо от ivanoff@ivan-chai.ru.\nпоставить в копию serge'o-lupin@mail.ru-",
    tgt=["ivanoff@ivan-chai.ru","serge'o-lupin@mail.ru"]
  ),
  dict(
    src="NO: foo.@ya.ru, foo@.ya.ru\nPARTLY:boo@ya_ru, -boo@ya.ru-, fooNoboo@ya.ru",
    tgt=["boo@ya","boo@ya.ru","boo@ya.ru"]
  )
]
"""
Рассмотрим только адреса, имя которых состоит из не более, чем 64 латинских букв, цифр и символов
'._+-, а домен — из не более, чем 255 латинских букв, цифр и символов .-. Ни Local-part, ни Domain part не
может начинаться/заканчиваться на .+-, а ещё в адресе не может быть более 1 точки подряд.
На вход даётся текст. Необходимо вывести все email адреса. Введем 3 ограничения: две точки внутри
адреса не встречаются; две @ внутри не встречаются; считаем, что email может быть частью «слова», то
есть в boo@ya_ru мы видим адрес boo@ya, а в fooNoboo@ya.ru видим boo@ya.ru.
"""

def extract_emails(text):
  doubledots = "(?!.*\.{2})"
  username = "[a-zA-Z0-9][a-zA-Z0-9'._+-]{0,62}[a-zA-Z0-9]"
  domain = "[a-zA-Z0-9][a-zA-Z0-9.-]{0,253}[a-zA-Z0-9]"
  regex = f"{doubledots}{username}@{domain}"
  matches = re.findall(regex,text)
  result = [m for m in matches if m.count(".")<2]
  return result

print("-"*30)
print("-"*30)
for i,text in enumerate(test_strings):
  mails = extract_emails(text['src'])
  if mails == text['tgt']:
    print(f"{i+1} фрагмент текста обработан корректно. Ожидалось: {text['tgt']}\nПолучено: {mails}")
  else:
    print(f"Обнаружено несоответствие. Ожидалось: {text['tgt']}\nПолучено: {mails}")
  print("-"*30)
  print("-"*30)
