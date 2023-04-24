# Вариант 18. В каждом задании обязательно использование модуля, которому посвящено задание.

## ЗАДАНИЕ 1. Модули PICKLE и DATETIME
Выполняется на основе выполненного задания третьей темы:

-  Необходимо создать текстовый файл и реализовать функцию логирования (без использования модуля
logging). Функция должна вызываться из каждого метода ранее реализованных классов и записывать в
файл строки следующего содержания: КЛЮЧ --- ДАТА И ВРЕМЯ --- КОММЕНТАРИЙ.
Ключи: CRE (создание экземпляра класса), INF (изменение), ERR (сработало исключение).
Комментарий: создано ..., удален ..., добавлен ..., распечатан ...
- Создать заполненные экземпляры реализованных класса, сериализовать их. В другом питоновском файле
импортировать файл с описанием класса и десериализовать объекты. Применить к десериализованным
объектам различные методы.

## ЗАДАНИЕ 2. Модуль MATH
– Реализовать две функции, вычисляющие математические формулы (файл math_task_X.png). Параметры
формул являются аргументами функций.

## ЗАДАНИЕ 3. Модуль RE
Показать выполненное тестирование.
– Задача. Поиск email
Рассмотрим только адреса, имя которых состоит из не более, чем 64 латинских букв, цифр и символов
'._+-, а домен — из не более, чем 255 латинских букв, цифр и символов .-. Ни Local-part, ни Domain part не
может начинаться/заканчиваться на .+-, а ещё в адресе не может быть более 1 точки подряд.
На вход даётся текст. Необходимо вывести все email адреса. Введем 3 ограничения: две точки внутри
адреса не встречаются; две @ внутри не встречаются; считаем, что email может быть частью «слова», то
есть в boo@ya_ru мы видим адрес boo@ya, а в fooNoboo@ya.ru видим boo@ya.ru.
| Ввод | Вывод|
|:----:|:----:|
|Нужен ответ на письмо от ivanoff@ivan-chai.ru.|ivanoff@ivan-chai.ru|
|поставить в копию serge'o-lupin@mail.ru-|serge'o-lupin@mail.ru|
|NO: foo.@ya.ru, foo@.ya.ru PARTLY:boo@ya_ru, -boo@ya.ru-, fooNoboo@ya.ru|boo@ya boo@ya.ru boo@ya.ru|

**UPD**: касательно `fooNoboo@ya.ru -> boo@ya.ru` было сказано, что опечатка, т.к. даже если игнорировать верхний регистр, то результат будет `oboo@ya.ru`, хотя верхний регистр обычно учитывается в адресе (и приводится к нижнему)

## ЗАДАНИЕ 4. Различные модули для работы с платформой и операционной системой

- Собрать в папке файлы «`task_****.py`» – все ранее решенные задачи из тем A, B.
- Написать функцию, которая создаст папку «Ознакомительная папка» с двумя подпапками («тема A», «тема B»), переместит все файлы в правильные подпапки.
- Написать функцию, которая получает адрес ранее созданной папки «Ознакомительная папка» и выполнит обход всех подпапок и:
  - чтение всех «task_****.py» файлов, нахождение в тексте названия функции и параметров
  - программный запуск и выполнение данных файлов, подсчет времени выполнения

Результат работы функции:
```py
folder "тема А":
>>>> script "task_A111.py"
>>>> >>>> function "sum_cube(n,m)"
>>>> >>>> output "TEST PASSED"
>>>> >>>> time "1.135 sec"
>>>> script "task_A222.py"
>>>> >>>> function "find_unique(lst)"
>>>> >>>> output "TEST PASSED"
>>>> >>>> time "2.005 sec"

```