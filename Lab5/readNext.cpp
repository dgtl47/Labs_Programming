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