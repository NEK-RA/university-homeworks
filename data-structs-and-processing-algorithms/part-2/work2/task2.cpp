#include "task2.h"
#include <cstring>


vector<friendInfo> readTxt(string filename){
    fstream txt;
    vector<friendInfo> result;
    friendInfo tmpf;
    date tmpd;
    if(!txt.is_open()){
        txt.open(filename, ios::in);
    }
    if(txt.is_open()){
        unsigned int day, month, year;
        char name[20];
        while(!txt.eof()){
            txt >> day;
            if(txt.fail()){
                txt.ignore(100,'\n');
                continue;
            }else{
                txt.ignore(1);
            }

            txt >> month;
            if(txt.fail()){
                txt.ignore(100,'\n');
                continue;
            }else{
                txt.ignore(1);
            }

            txt >> year;
            if(txt.fail()){
                txt.ignore(100,'\n');
                continue;
            }else{
                txt.ignore(1);
            }

            txt.getline(name, sizeof(name), '\n');

            tmpd = {day, month, year};
            tmpf.birthday = tmpd;
            strncpy(tmpf.name, name, sizeof(tmpf.name));

            result.push_back(tmpf);
        }
        txt.close();
    }else{
        cout << "Не удалось открыть текстовый файл для чтения" << endl;
    }
    return result;
}


string txt2bin(string filename){
    vector<friendInfo> friends = readTxt(filename);
    if(friends.size() > 0){
        fstream bin;
        if(!bin.is_open()){
            bin.open(filename+".bin", ios::out | ios::binary);
        }
        if(bin.is_open()){
            for(friendInfo f : friends){
                bin.write(
                    reinterpret_cast<char*>(&f),
                    sizeof(f)
                    );
            }
            bin.close();
            return filename+".bin";
        }else{
            cout << "Не удалось открыть бинарный файл для записи" << endl;
            return "";
        }
    }else{
        cout << "Текстовый файл не содержит подходящих данных" << endl;
        return "";
    }
}


vector<friendInfo> readBin(string filename){
    fstream bin;
    vector<friendInfo> result;
    friendInfo tmpf;
    if(!bin.is_open()){
        bin.open(filename, ios::in | ios::binary);
    }
    if(bin.is_open()){
        while(!bin.eof()){
            bin.read(
                reinterpret_cast<char*>(&tmpf),
                sizeof(tmpf)
            );
            if(bin.fail()){
                bin.ignore(1);
                continue;
            }

            result.push_back(tmpf);
        }
        bin.close();
    }else{
        cout << "Не удалось открыть бинарный файл для чтения" << endl;
    }
    return result;
}


string bin2txt(string filename){
    vector<friendInfo> friends = readBin(filename);
    if(friends.size() > 0){
        fstream txt;
        if(!txt.is_open()){
            txt.open(filename+".csv", ios::out);
        }
        if(txt.is_open()){
            for(friendInfo f : friends){
                txt << f.birthday.day << ","
                    << f.birthday.month << ","
                    << f.birthday.year << ","
                    << f.name << endl;
            }
            txt.close();
            return filename+".csv";
        }else{
            cout << "Не удалось открыть текстовый файл для записи" << endl;
            return "";
        }
    }else{
        cout << "Бинарный файл не содержит подходящих данных" << endl;
        return "";
    }
}


friendInfo readNthFriend(string filename, int n){
    friendInfo empty;
    empty.birthday = {0,0,0};
    strncpy(empty.name, ((string)"НЕТ РЕЗ-ТА").c_str(), sizeof(empty.name));
    if(n < 1){
        cout << "Номер записи должен быть от 1 и более" << endl;
    }else{
        fstream bin;
        if(!bin.is_open()){
            bin.open(filename, ios::in | ios::binary);
        }
        if(bin.is_open()){
            friendInfo result;
            bool fail = false;

            bin.seekg(0, ios_base::end);
            int fileSize = bin.tellg();
            int totalRecords = fileSize / sizeof(result);
            if(n > totalRecords){
                cout << "В файле всего " << totalRecords << " записей, номер " << n << " - отсутствует" << endl;
                fail = true;
            }
            if(!fail){
                bin.seekg((n-1)*sizeof(result));
                bin.read(
                    reinterpret_cast<char*>(&result),
                    sizeof(result)
                    );
                if(bin.fail()){
                    cout << "Не удалось считать данные" << endl;
                    fail = true;
                }
            }
            bin.close();
            if(fail){
                return empty;
            }else{
                return result;
            }
        }else{
            cout << "Не удалось открыть " << filename << " для чтения." << endl;
        }
    }
    return empty;
}


void deleteRecord(string filename, string key){
    // ключ - имя
    vector<friendInfo> records = readBin(filename);
    int index = -1;
    for(vector<friendInfo>::iterator i = records.begin(); i != records.end(); i++){
        if((string)(*i).name == key){
            records.erase(i);
            i--;
        }
    }
    fstream bin;
    if(records.size() > 0){
        fstream bin;
        if(!bin.is_open()){
            bin.open(filename, ios::out | ios::binary);
        }
        if(bin.is_open()){
            for(friendInfo f : records){
                bin.write(
                    reinterpret_cast<char*>(&f),
                    sizeof(f)
                    );
            }
            bin.close();

        }else{
            cout << "Не удалось открыть бинарный файл для перезаписи" << endl;
        }
    }else{
        cout << "Не осталось данных для записи" << endl;
    }
}


string byMonth2Txt(string filename, int month){
    fstream bin;
    fstream txt;
    friendInfo tmpf;
    if(month < 1 || month > 12){
        cout << "Некорректное значение месяца" << endl;
        return "";
    }
    if(!bin.is_open()){
        bin.open(filename, ios::in | ios::binary);
    }
    if(!txt.is_open()){
        txt.open(filename + ".csv", ios::out);
    }
    if(bin.is_open() && txt.is_open()){
        while(!bin.eof()){
            bin.read(
                reinterpret_cast<char*>(&tmpf),
                sizeof(tmpf)
                );
            if(bin.fail()){
                bin.ignore(1);
                continue;
            }
            if(tmpf.birthday.month == month){
                txt << tmpf.birthday.day << ","
                    << tmpf.birthday.month << ","
                    << tmpf.birthday.year << ","
                    << tmpf.name << endl;
            }
        }
        bin.close();
        txt.close();
    }else{
        if(bin.is_open()){
            bin.close();
        }
        if(txt.is_open()){
            txt.close();
        }
        cout << "Не удалось открыть бинарный файл для чтения" << endl;
    }
    return filename + ".csv";
}


vector<string> searchByDate(string filename,date target){
    fstream bin;
    vector<string> results;
    friendInfo tmpf;
    if(!bin.is_open()){
        bin.open(filename, ios::in | ios::binary);
    }
    if(bin.is_open()){
        while(!bin.eof()){
            bin.read(
                reinterpret_cast<char*>(&tmpf),
                sizeof(tmpf)
            );
            if(bin.fail()){
                bin.ignore(1);
                continue;
            }

            if(tmpf.birthday.day == target.day &&
                tmpf.birthday.month == target.month &&
                tmpf.birthday.year == target.year){
                cout << "Добавляем имя " << tmpf.name << endl;
                results.push_back(tmpf.name);
            }
        }

        bin.close();
    }else{
        cout << "Не удалось открыть бинарный файл для чтения" << endl;
    }
    return results;
}

/*
Разработать программу управления двоичными файлами с записями
фиксированной длины. Общие требования: файл состоит из записей определенной
структуры, согласно варианту. Записи имеют ключ, уникальный в пределах файла.

2.1. Разработать структуру записи двоичного файла согласно варианту задания:
Вариант 15:
> Структура записи "Найти и поздравить друга: дата рождения, имя"
> Доп. операция

2.2. Подготовить тестовые данные в текстовом файле с кодировкой ASCII, в
соответствии со структурой записи варианта. При открытии файла выполнить
контроль его существования и открытия.
++ 2.3. Имя файла вводит пользователь.
++ 2.4. При открытии файла обеспечить контроль существования и открытия файла.

2.5. При применении механизма прямого доступа к записи файла выполнить
контроль присутствия записи с заданным номером в файле.

2.6. Разработать функции для выполнения операций:
++ 2.6.1. преобразование тестовых данных из текстового файла в двоичный файл;
++ 2.6.2. преобразование данных из двоичного файла в текстовый;
++ 2.6.3. вывод всех записей двоичного файла;
++ 2.6.4. доступ к записи по ее порядковому номеру в файле, используя механизм
прямого доступа к записи в двоичном файле;
2.6.5. удаление записи с заданным значением ключа, выполнить путем замены
на последнюю запись.
++ 2.6.6. манипулирование записями в двоичном файле согласно дополнительным
операциям, определенным в варианте;
    > ++ 1. Сформировать в текстовом файле список друзей, родившихся в указанном месяце.
    > ++ 2. Указать имя, родившегося в заданную дату.
*/

void printFriend(friendInfo f){
    cout << setw(10) << f.birthday.day
         << setw(10) << f.birthday.month
         << setw(10) << f.birthday.year
         << setw(20) << f.name
         << endl;
}

//бинарник в ~/dev/cpp/builds/build-work2-Desktop_Qt_6_5_2_GCC_64bit-Debug/

void task2(){
    string filename;
    string name;
    vector<friendInfo> friends;
    int choice = -1;
    int n = 0;
    unsigned int day = 0, month = 0, year = 0;
    vector<string> names;
    string menu = "1. Преобразовать текст в двоичный файл\n"
                  "2. Преобразование двоичного файла в текст\n"
                  "3. Вывод всех записей двоичного файла\n"
                  "4. Доступ к записи по ее порядковому номеру\n"
                  "5. Удалить запись по ключу\n"
                  "6. Список друзей, родившихся в указанном месяце в текст\n"
                  "7. Указать имя родившегося в заданную дату\n"
                  "0. Вернуться назад\n"
                  "Ваш выбор: ";
    while(choice != 0){
        cout << endl << menu;
        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        switch(choice){
        case 1:
            cout << "Укажите имя файла: ";
            cin >> filename;
            filename = txt2bin(filename);
            cout << endl << "Бинарные данные записаны в файл: " << filename << endl;
            break;

        case 2:
            cout << "Укажите имя файла: ";
            cin >> filename;
            filename = bin2txt(filename);
            cout << endl << "текстовые данные записаны в файл: " << filename << endl;
            break;

        case 3:
            cout << "Укажите имя файла: ";
            cin >> filename;
            friends = readBin(filename);
            cout << endl;
            if(friends.size() > 0){
                cout << setw(10) << "DAY"
                     << setw(10) << "MONTH"
                     << setw(10) << "YEAR"
                     << setw(20) << "NAME"
                     << endl;
                for(friendInfo f : friends){
                    printFriend(f);
                }
            }else{
                cout << "Записей нет." << endl;
            }
            break;

        case 4:
            cout << "Укажите имя бинарного файла: ";
            cin >> filename;
            cout << "Укажите номер записи в файле: ";
            cin >> n;
            printFriend(readNthFriend(filename, n));
            break;

        case 5:
            cout << "Укажите имя редактируемого файла: ";
            cin >> filename;
            cout << "Введите имя человека, запись о котором надо удалить: ";
            cin >> name;
            deleteRecord(filename, name);
            break;

        case 6:
            cout << "Укажите имя обрабатываемого файла: ";
            cin >> filename;
            cout << "Укажите номер месяца (январь = 1): ";
            cin >> month;
            filename = byMonth2Txt(filename, month);
            cout << "Данные записаны в: " << filename << endl;
                break;

        case 7:
            cout << "Укажите имя обрабатываемого файла: ";
            cin >> filename;
            cout << "Укажите число: ";
            cin >> day;
            cout << "Укажите номер месяца (январь = 1): ";
            cin >> month;
            cout << "Укажите год: ";
            cin >> year;
            names = searchByDate(filename, {day, month, year});
            if(names.size() == 0){
                cout << "Нет друзей, родившихся в эту дату." << endl;
            }else{
                cout << "В этот день родились: ";
                for (string name : names){
                    cout << name << " ";
                }
                cout << endl;
            }
            break;

        default:
            cout << string(50,'-') << endl;
        }
    }
}
