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