description="Напишите сценарий, который выводит дату, время, список зарегистрировавшихся пользователей, и uptime системы и сохраняет эту информацию в файл."

echo -e "Задание 1\n$description\n\n"

now_str="Текущая дата: $(TZ="UTC-3" date --rfc-3339="seconds")"
uptime_str="$(uptime | egrep -o "up.*user" | sed -E 's/, +[0-9]+ +user//g' | sed -E 's/ +/ /g' | sed 's/up/Аптайм системы:/g' | sed -E 's/day[s]?/дней/g' | sed -E 's/, +/ и /g') часов"
users_str="Зарегистрированные пользователи:\n$(awk -F: '$3 == 0 || $3 >= 1000 && $3 < 65534 {print $1"(uid="$3")"}' /etc/passwd | xargs | sed -E 's/ +/, /g')"
echo -e "$now_str\n\n$users_str\n\n$uptime_str" > summary.txt
cat summary.txt
