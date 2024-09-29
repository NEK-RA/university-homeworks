description="Напишите сценарий, который с помощью цикла прочитает файл и выведет его содержимое."

echo -e "Задание 3\n$description\n\n"

if [[ -f $1 ]];
then
  while IFS= read -r line
  do
    echo "$line"
  done < $1
else
  echo "Файл '$1' не найден"
fi