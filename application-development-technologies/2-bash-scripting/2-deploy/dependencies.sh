echo "Поиск зависимостей"

python_files=$(find | egrep ".py$")
import_lines=()

echo "Поиск строк с импортами"
for file in $python_files; do
  scoped_imports=$(grep -E "^\s*import |^\s*from .* import " "$file")
  while read -r line; do
    if [[ -n "$line" ]]; then 
      import_lines+=("$line")
    fi
  done < <(echo "$scoped_imports")
done
unset python_files


echo "Обнаружено строк с импортами: ${#import_lines[@]}"

echo "Выделяем названия пакетов из строк импорта"
echo "Избавляемся от относительных локальных импортов ('import .mod')"
echo "Отфильтровываем импорты пакетов верхнего уровня"

declare -A packages
for line in "${import_lines[@]}"; do
  if echo "$line" | grep -q "from"; then
    package=$(echo "$line" | egrep -o "from.*import" | sed -E 's/(import|from)//g' | sed -E 's/ +//g')
    if [[ ! "$package" =~ ^\..* ]]; then
      if [[ "$package" =~ [^.]+\. ]]; then
        package=$(echo "$package" | cut -d . -f 1)
      fi
      packages["$package"]=1
    fi
  else
    package=$(echo "$line" | sed 's/import//g' | sed -E 's/ +//g')
    if [[ ! "$package" =~ ^\..* ]]; then
      if [[ "$package" =~ [^.]+\. ]]; then
        package=$(echo "$package" | cut -d . -f 1)
      fi
      packages["$package"]=1
    fi
  fi
done
unset import_lines

echo "Избавляемся от локальных импортов относительно корня проекта"

modules=()

tasks_root=$(pwd)
cd blocknote-master/apps
folder_items=$(ls | xargs)
cd $tasks_root

for package in "${!packages[@]}"; do
  for item in $folder_items; do
    if [[ "$package" == "$item" ]]; then
      continue 2
    fi
  done
  modules+=("$package")
done
unset packages

echo "Осталось пакетов: ${#modules[@]}"

echo "Запрашиваем у Python список встроенных пакетов"
help_mods=$(python -c "help('modules')")
builtins=$(echo $help_mods | egrep -o "\.{3}.*Enter any" | sed -E "s/\.{3}//g" | sed "s/Enter any//g")

echo "Удаляем из списка зависимостей пакеты, предоставляемые стандартной библиотекой Python"

dependencies=()
for module in "${modules[@]}"; do
  if [[ ! "$builtins" =~ "$module" ]]; then
    dependencies+=("$module")
  fi
done
unset modules

echo "Финальный список зависимостей (${#dependencies[@]} пакетов):"
echo "${dependencies[@]}"
if [[ -f requirements.txt ]]; then
  rm raw_requirements.txt
fi
touch raw_requirements.txt
for dep in "${dependencies[@]}"; do
  echo $dep >> raw_requirements.txt
done
echo "Данные сохранены в файл raw_requirements.txt"