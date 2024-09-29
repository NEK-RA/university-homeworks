description="Напишите сценарий, который подсчитает объем диска, занимаемого директорией. В качестве директории можно выбрать любую директорию в системе"

echo -e "Задание 5\n$description\n\n"

if [[ -d $1 ]]; then
  files=$(find $1 | xargs)
  total_size=0
  for file in $files; do
    filesize=$(stat -c %s $file)
    (( total_size += filesize))
  done
  bytes=$total_size
  size_entities="байт килобайт мегабайт гигабайт"
  total_size_entity=1
  while (( $(echo "$total_size > 1024" | bc) )); do
    total_size=$(echo "scale=2; $total_size / 1024" | bc)
    (( total_size_entity += 1 ))
  done
  final_size_entity=$(echo $size_entities | cut -d " " -f $total_size_entity)
  echo "Каталог $1 занимает $total_size $final_size_entity(а) / $bytes байт(а)"
else
  echo "Каталог '$1' не найден"
fi