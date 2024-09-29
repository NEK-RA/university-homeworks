description="Напишите сценарий, который выведет список всех исполняемых файлов в директории, для которых у текущего пользователя есть права на исполнение."

echo -e "Задание 6\n$description\n\n"

files=$(ls -A)
# files=$(find)

echo "Список исполняемых файлов в данной директории:"
for file in $files; do
  if [[ -f $file && -x $file ]]; then
    echo -en "$file\t"
  fi
done
echo -en "\n"