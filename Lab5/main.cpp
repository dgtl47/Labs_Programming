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