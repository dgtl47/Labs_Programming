#include <iostream>
#include "libbmp.h"

// Ключ: 11r 11g 11b 10r 10g 10b 01r 01g

short currentBit = 7;  // Переменная, хранящая номер текущего читаемого бита
short currentByte = 0; // Переменная, хранящая номер текущего читаемого байта
char text[3138];       // Массив, для сохранения читаемого текста внутри  

// Флаг, предотвращающий лишние чтение/запись после достижения '\0'
bool isEndReached = false;

// Добавить новый бит в строку
void addBit(char bit)
{
    if (isEndReached) return;

    // Установка бита в нужную позицию при помощи сдвига
    text[currentByte] |= bit << currentBit--;

    // Переход к следующему байту
    if (currentBit < 0)
    {
        if (text[currentByte] == '\0') {
            isEndReached = true;
            return;
        }

        currentBit = 7;
        currentByte++;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Создание обработчика изображений и его инициализация
    BmpImg img;
    img.read("pic4.bmp");

    // Движение снизу вверх и справа налево
    for (int x = img.get_width() - 1; x >= 0; x--)
    {
        for (int y = img.get_height() - 1; y >= 0; y--)
        {
            if (x == 0 && y == 0) break;

            char bit1 = img.red_at(x, y) & 1;
            char bit2 = img.green_at(x, y) & 1;
            char bit3 = img.blue_at(x, y) & 1;

            addBit(bit1); addBit(bit2); addBit(bit3);
            if (isEndReached) break;
        }
        if (isEndReached) break;
    }

    std::cout << text << "\n\n\n\n\n";
}