МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ

Федеральное государственное автономное образовательное учреждение высшего образования
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе № 5<br/> по дисциплине "Программирование"
<br/>
​
Cтудента 1 курса группы ПИ-б-о-191(2)<br/>
Влахова Артема Александровича<br/>
направления 09.03.04 "Программная инженерия"<br/>
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
​
Симферополь, 2019

* * *

## Цель:

1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.

## Ход работы

Перед выполнением данной лабораторной работы, моим первым шагом было скачать необходимый файл из репозитория и поместить его в папку к созданному проекту (Рис. 1).

![Изображение№1](/Lab5/Screenshots/1.png "Рис.1")\
*Рис.1 Созданный проект*

Проанализировав data_dictionary.txt и сам train.csv, я реализовал следующую структуру для хранения данных о пассажире (Рис. 2):

![Изображение№2](/Lab5/Screenshots/2.png "Рис.2")\
*Рис.2 Созданная структура данных для чтения train.csv*

Я разделил свою программу на три основных файла и два вспомогательных:

1. main.cpp, содержащий в себе основной код чтения из train.csv и сборки финального расчёта.
2. passenger.cpp, содержащий в себе реализацию функций по инициализации структуры Passenger, а так же превращения enum Embarkation в строку
3. passenger.h, являющийся заголовочным файлом для passenger.cpp
4. readNext.cpp, содержащий в себе реализации функций по упрощению разделения строки на лексемы и дальнейшей конвертации в различные типы.
5. readNext.h - заголовочный файл readNext.cpp.

Как выглядит мой финальный код:

**passenger.h**

```cpp
#ifndef PASSENGER_H
#define PASSENGER_H

enum Class {
    Upper,
    Middle,
    Lower,
};

enum Sex {
    Male,
    Female
};

enum Embarkation {
    Cherbourg,
    Queenstown,
    Southampton
};

// Преобразование Embarkation в строку
std::string printEmbarkation(Embarkation em);

struct Passenger {
    short id;
    bool hasSurvived;
    Class pClass;
    std::string name;
    Sex sex;
    float age;
    short sibsp;
    short parch;
    std::string ticket;
    float fare;
    std::string cabin;
    Embarkation embarkation;
};

// Инициализация пассажира по строке из CSV файла
void initPassenger(Passenger* psg, char* string);

// Debug
void printPassenger(Passenger psg);

#endif
```

**readNext.h**

```cpp
#ifndef READNEXT_H
#define READNEXT_H

// Аналог strtok, который может читать пустые лексемы
char* readUntil(char* string, char delim);

// readUntil, который возвращает std::string
std::string readNextStr(char* string, char delim);

// Чтение имени пассажира
std::string readNextName(char* string);

// readUntil, который возвращает int
int readNextInt(char* string, char delim, int defaultValue = -1);

// readUntil, который возвращает bool
bool readNextBool(char* string, char delim);

// readUntil, который возвращает float
float readNextFloat(char* string, char delim, float defaultValue = -1.0);

#endif
```

**passenger.cpp**

```cpp
#include <iostream>

#include "passenger.h"
#include "readNext.h"

std::string printEmbarkation(Embarkation em) {
    switch (em) {
        case Cherbourg:
            return "Cherbourg";
        case Queenstown:
            return "Queenstown";
        case Southampton:
            return "Southampton";

        default:
            return "Unknown";
    }
}

void initPassenger(Passenger* psg, char* string) {
    // PassengerId, Survived, Pclass, Name, Sex, Age, SibSp, Parch, Ticket, Fare, Cabin, Embarked

    // Читаем все поля подряд
    psg->id = readNextInt(string, ',');
    psg->hasSurvived = readNextBool(nullptr, ',');
    psg->pClass = static_cast<Class>(readNextInt(nullptr, ',') - 1);
    psg->name = readNextName(nullptr);    // Читаем имя по отдельным правилам
    psg->sex = readNextStr(nullptr, ',') == "male" ? Male : Female;
    psg->age = readNextFloat(nullptr, ',');    //-1.0 если пропущено
    psg->sibsp = readNextInt(nullptr, ',');
    psg->parch = readNextInt(nullptr, ',');
    psg->ticket = readNextStr(nullptr, ',');
    psg->fare = readNextFloat(nullptr, ',');
    psg->cabin = readNextStr(nullptr, ',');   // Пустая строка, если пропущено

    std::string embarked = readNextStr(nullptr, '\0');
    if (embarked == "S") psg->embarkation = Southampton;
    else if (embarked == "Q") psg->embarkation = Queenstown;
    else psg->embarkation = Cherbourg;
}

// Debug
void printPassenger(Passenger psg) {
    std::cout << '"' << psg.id << " " << psg.hasSurvived << " " << psg.pClass << " " << psg.name << " "
        << psg.sex << " " << psg.sibsp << " " << psg.parch << " " << psg.ticket << " " << psg.fare << " "
        << psg.cabin << " " << psg.embarkation << '"' << '\n';
}
```

**readNext.cpp**

```cpp
#include <cstring>
#include <iostream>

// Аналог strtok, который может читать пустые лексемы
char* readUntil(char* string, char delim) {
    static char* lastPos;
    if (string != nullptr) lastPos = string;

    char* start = lastPos;
    int i = 0;
    while (lastPos[i] != '\0') {
        if (lastPos[i] == delim) {
            lastPos[i] = '\0';
            lastPos += i + 1;

            return start;
        }

        i++;
    }

    return start;
}

std::string readNextStr(char* string, char delim) {
    return readUntil(string, delim);
}

// Чтение имени
std::string readNextName(char* string) {
    std::string name;

    name = readNextStr(string, ',');            // Это считает строку до первой запятой (вместе с первой кавычкой)
    name += "," + readNextStr(nullptr, ',');     // Это считывает строку до конца, включая последнюю кавычку
    name = name.substr(1, name.length() - 2);    // Удаляем кавычки в начале и конце

    // Удаляем возможные сдвоенные кавычки
    for (int i = 0; i < name.length() - 1; i++) {
        // Если найдены две кавычки подряд
        if (name.substr(i, 2) == "\"\"") {
            name.erase(i, 1);
        }
    }

    return name;
}

int readNextInt(char* string, char delim, int defaultValue = -1) {
    char* lexem = readUntil(string, delim);
    if (strlen(lexem) == 0) return defaultValue;

    return atoi(lexem);
}

bool readNextBool(char* string, char delim) {
    return readNextInt(string, delim, 0);
}

float readNextFloat(char* string, char delim, float defaultValue = -1.0) {
    char* lexem = readUntil(string, delim);
    if (strlen(lexem) == 0) return defaultValue;

    return atof(lexem);
}
```

**main.cpp**

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

// Файл с вспомогательными функциями для анализа строки
#include "readNext.h"
// Файл со структурой и остальным необходимым
#include "passenger.h"

std::vector<Passenger> passengers;

int main() {
    setlocale(LC_ALL, "Russian");

    std::ifstream fin("CSV/train.csv");
    if (!fin) {
        std::cout << "Не удалось открыть CSV/train.csv";
        exit(1);
    }
    std::ofstream fout("output.txt");
    if (!fout) {
        std::cout << "Не удалось открыть output.txt на запись";
        exit(1);
    }

    const int buffer_size = 200;
    char buffer[buffer_size];

    // Пропускаем первую строчку с заголовками (читаем и не используем)
    fin.getline(buffer, buffer_size, '\r');

    // Читаем все строчки, пока не достигнем конца файла
    while(fin.getline(buffer, buffer_size, '\r')) {
        // Создаём и инициализируем очередного пассажира
        Passenger psg;
        initPassenger(&psg, buffer);

        // Добавляем в вектор
        passengers.push_back(psg);
    }
    fin.close();

    /* Подсчёт нужных значений */
    int aliveTotal = 0;
    int aliveByClass[3] {};
    int aliveBySex[2] {};

    // Для среднего значения возраста
    int ageAmount = 0;
    double averageAge = 0;

    // Для среднего значения возраста по полу
    int ageAmountBySex[2] {};
    double averageBySex[2] {};

    int passengersInState[3] {};

    /* Подсчёт и запись в файл */
    for (int i = 0; i < passengers.size(); i++) {
        Passenger p = passengers[i];
        if (p.hasSurvived) {
            aliveTotal++;
            aliveByClass[p.pClass]++;
            aliveBySex[p.sex]++;
        }

        if (p.age != -1) {
            averageAge += p.age;
            ageAmount++;

            averageBySex[p.sex] += p.age;
            ageAmountBySex[p.sex]++;
        }

        passengersInState[p.embarkation]++;
    }

    if (ageAmount != 0)
        averageAge /= ageAmount;

    if (ageAmountBySex[Male] != 0)
        averageBySex[Male] /= ageAmountBySex[Male];
    if (ageAmountBySex[Female] != 0)
        averageBySex[Female] /= ageAmountBySex[Female];

    fout << "Общее число выживших: " << aliveTotal << '\n';
    fout << "Число выживших 1-го класса: " << aliveByClass[Upper] << '\n';
    fout << "Число выживших 2-го класса: " << aliveByClass[Middle] << '\n';
    fout << "Число выживших 3-го класса: " << aliveByClass[Lower] << '\n';
    fout << "Количество выживших женщин: " << aliveBySex[Female] << '\n';
    fout << "Количество выживших мужчин: " << aliveBySex[Male] << '\n';
    fout << "Средний возраст пассажира: " << averageAge << '\n';
    fout << "Средний женский возраст: " << averageBySex[Female] << '\n';
    fout << "Средний мужской возраст: " << averageBySex[Male] << '\n';

    // Находим штат с наибольшим числом пассажиров
    Embarkation max = Cherbourg;
    for (int i = 0; i < 3; i++) {
        Embarkation em = static_cast<Embarkation>(i);

        if (passengersInState[em] > passengersInState[max]) max = em;
    }
    fout << "Штат, в котором село больше всего пассажиров: ";
    fout << printEmbarkation(max);
    fout << '\n';

    // Список несовершеннолетних
    fout << "Список идентификаторов несовершеннолетних:\n";
    for (int i = 0; i < passengers.size(); i++) {
        Passenger p = passengers[i];
        if (p.age != -1 && p.age < 18) fout << p.id << ", ";
    }

    fout.close();
    return 0;
}
```

Ссылка на полученный файл:
[output.txt](/Lab5/output.txt)

* * *

## Вывод

Я научился работать с текстовыми файлами, закрепил навыки работы со структурами, закрепил навыки работы с множественными файлами в проекте.
