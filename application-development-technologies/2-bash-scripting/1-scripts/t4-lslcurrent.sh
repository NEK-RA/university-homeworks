description="Напишите сценарий, который с помощью цикла выведет список файлов и директорий из текущего каталога, укажет, что есть файл, а что директория."

echo -e "Задание 4\n$description\n\n"

items=$(ls -A)

echo -e "Файлы и папки в текущем каталоге:\n"
for item in $items; do
  if [[ -d $item ]]; then
    echo "Папка: $item"
  fi
done

for item in $items; do
  if [[ -f $item ]]; then
    echo "Файл: $item"
  fi
done