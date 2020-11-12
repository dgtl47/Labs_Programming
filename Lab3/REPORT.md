МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  

Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>
​
### Отчёт по лабораторной работе № 3<br/> по дисциплине "Программирование"
<br/>
​
Cтудента 1 курса группы ПИ-б-о-191(2)  
Влахова Артема Александровича
направления 09.03.04 "Программная инженерия"  
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

1. Закрепить навыки разработки программ использующих операторы цикла;
2. Закрепить навыки разработки программ использующих массивы;
3. Освоить методы подключения сторонних библиотек.

## Ход работы

Перед выполнением данной лабораторной работы я создал новый проект и запустил его, убеждаясь в работоспособности среды и компилятора (Рис. 1).

![Изображение№1](/Lab3/Screenshots/1.png "Рис.1")  
*Рис.1 Созданный проект*

Следующим шагом было склонировать репозиторий с библиотекой libbmp. Я делал это через WSL терминал (Рис. 2), после чего переместить нужные файлы в мой проект (Рис. 3).

![Изображение№2](/Lab3/Screenshots/2.png "Рис.2")  
*Рис.2 Клонирование libbmp*

![Изображение№3](/Lab3/Screenshots/3.png "Рис.3")  
*Рис.3 Перемещённые libbmp.h (папка include) и libbmp.cpp*

Дальше папка "include" была добавлена как дополнительный каталог включаемых файлов (Рис.4), добавлен libbmp.cpp как доп файл (Рис.5) и *libbmp.h* было подключено через директиву "#include" (Рис.6).

![Изображение№4](/Lab3/Screenshots/8.png "Рис.4")  
*Рис.4 Добавление папки include как дополнительный каталог включаемых файлов*

![Изображение№5](/Lab3/Screenshots/6.png "Рис.5")  
*Рис.5 Добавленный libbmp.cpp в проект*

![Изображение№6](/Lab3/Screenshots/9.png "Рис.6")  
*Рис.6 Подключение libbmp.h*

* * *

Мой вариант - четвертый, поэтому я скачал следующее изображение (Рис. 7):

![Изображение№7](/Lab3/Screenshots/pic4.bmp "Рис.7")  
*Рис.7 Моё изображение со спрятанным внутри сообщением*

Вместе с ним шёл следующий ключ:

```11r 11g 11b 10r 10g 10b 01r 01g```

Этот ключ означает, что начать дешифровку нужно с нижнего левого края и идти снизу вверх и справа налево.

Для решения задачи я написал следующую задачу:

```cpp
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

            // Получаем младший бит (остальные = 0)
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
```

Данная программа выдаёт следующий результат (Рис. 8 и блок текста):

![Изображение№8](/Lab3/Screenshots/11.png "Рис.8")  
*Рис.8 Результат работы программы*

```txt
James Madison Jr. (March 16, 1751[b] - June 28, 1836) was an American statesman, lawyer, diplomat, philosopher and Founding Father who served as the fourth president of the United States from 1809 to 1817. He is hailed as the "Father of the Constitution" for his pivotal role in drafting and promoting the Constitution of the United States and the United States Bill of Rights. He co-wrote The Federalist Papers, co-founded the Democratic-Republican Party, and served as the fifth United States secretary of State from 1801 to 1809.
Born into a prominent Virginia planter family, Madison served as a member of the Virginia House of Delegates and the Continental Congress during and after the American Revolutionary War. He became dissatisfied with the weak national government established by the Articles of Confederation and helped organize the Constitutional Convention, which produced a new constitution to supplant the Articles of Confederation. Madison's Virginia Plan served as the basis for the Constitutional Convention's deliberations, and he was one of the most influential individuals at the convention. Madison became one of the leaders in the movement to ratify the Constitution, and he joined with Alexander Hamilton and John Jay in writing The Federalist Papers, a series of pro-ratification essays that is widely considered to be one of the most influential works of political science in American history.
After the ratification of the Constitution, Madison emerged as an important leader in the United States House of Representatives and served as a close adviser to President George Washington. He was the main force behind the ratification of the United States Bill of Rights, which enshrines guarantees of personal freedoms and rights within the Constitution. During the early 1790s, Madison came to oppose the economic program and accompanying centralization of power favored by Secretary of the Treasury Alexander Hamilton. Along with Thomas Jefferson, Madison organized the Democratic-Republican Party, which was, alongside Hamilton's Federalist Party, one of the nation's first major political parties. After Jefferson won the 1800 presidential election, Madison served as secretary of State from 1801 to 1809. In that position, he supervised the Louisiana Purchase, which doubled the size of the United States.
Madison succeeded Jefferson with a victory in the 1808 presidential election. After diplomatic protests and a trade embargo failed to end British attacks against American shipping, he led the United States into the War of 1812. The war was an administrative morass and ended inconclusively, but many Americans saw it as a successful "second war of independence" against Britain. The war convinced Madison of the necessity of a stronger federal government, and he presided over the creation of the Second Bank of the United States and the enactment of the protective Tariff of 1816. He retired from public office in 1817 and died in 1836. Madison is considered to be one of the most important Founding Fathers of the United States, and historians have generally ranked him as an above-average president.
```

* * *

## Вывод

Я закрепил навыки разработки программ, использующих операторы цикла, а так же программ, использующих массивы на примере декодирования текста из изображения. Освоил методы подключения сторонних библиотек.
