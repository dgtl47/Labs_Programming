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