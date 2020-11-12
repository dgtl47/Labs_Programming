МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ\
Федеральное государственное автономное образовательное учреждение высшего образования\
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"\
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ\
Кафедра компьютерной инженерии и моделирования\
<br/><br/>
​
### Отчёт по лабораторной работе № 7<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(2)\
Влахова Артема Александровича\
направления подготовки 09.03.04 "Программная инженерия"\
<br/>
​
<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/>компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
​
Симферополь, 2019

* * *

## Цель: _изучить основные возможности создания и отладки программ в IDE Qt Creator_

## Ход работы

    1. Как создать консольное приложение С++ в IDE Qt Creator без использования компонентов Qt?

Консольное приложение (как и аналогичные проекты Qt Creator) создаются в три шага:

* Файл -> Создать файл или проект...
* Выбрать раздел "Проект без Qt", а затем "Приложение на языке C++"
* Выбрать название и расположения проекта, а так же поменять при необходимости другие настройки.

![Изображение#1](Screenshots/1.png "Рис. 1")\
*Рис.1 Первый шаг создания проекта*

![Изображение#2](Screenshots/2.png "Рис. 2")\
*Рис.2 Выбор типа проекта*

![Изображение#3](Screenshots/24.png "Рис. 3")\
*Рис.3 Выбор названия и расположения проекта*

* * *

    2. Как изменить цветовую схему (оформление) среды?

Цветовая схема Qt Creator меняется через "Параметры", расположенные в графе "Инструменты"

* Открыть Инструменты -> Параметры...
* Убедиться, что в левой части открывшегося окна выбрана вкладка "Среда"
* В правой части выбрать нужную цветовую схему

![Изображение#4](Screenshots/4.png "Рис. 4")\
*Рис.4 Расположение параметров*

![Изображение#5](Screenshots/25.png "Рис. 5")\
*Рис.5 Изменение темы в настройках*

* * *

    3. Как закомментировать/раскомментировать блок кода средствами Qt Creator?

Комментирование и раскомментирование в Qt Creator производится одним сочетанием клавиш, предварительно поставив каретку на нужную строчку.

* *Ctrl + /* комментирует/декомментирует строчку.

Пример работы (см. рис. 6)

![Изображение#6](Screenshots/6.png "Рис. 6")\
*Рис.6 Что происходит после нажатия Ctrl + /*

* * *

    4. Как открыть в проводнике Windows папку с проектом средствами Qt Creator?

Открыть проводник для выбора папки можно двумя способами:

* Использовать сочетание клавиш *Ctrl + O*
* Перейти по Файл -> Открыть файл или проект...

После чего в проводнике нужно выбрать *.pro* (файл проекта Qt Creator) и нажать "Открыть"

![Изображение#7](Screenshots/7.png "Рис. 7")\
*Рис.7 Расположение кнопки для открытия папки*

* * *

    5. Какое расширение файла-проекта используется Qt Creator?

Qt Creator использует *.pro* в качестве расширения для файла проекта.

![Изображение#8](Screenshots/8.png "Рис. 8")\
*Рис.8 Файл проекта Qt Creator*

* * *

    6. Как запустить код без отладки?

Запустить код без отладки можно тремя способами:

* Нажатием _Ctrl + R_
* Навигацией в левую нижнюю часть экрана и нажатию на зеленый треугольник без инонки жука
* Переходом на вкладку Сборка -> Запустить

![Изображение#9](Screenshots/26.png "Рис. 9")\
*Рис.9 Запуск без отладки через иконку запуска в левом нижнем углу экрана (конфигурация проекта не важна)*

![Изображение#10](Screenshots/9.png "Рис. 10")\
*Рис.10 Запуск без отладки через Сборка -> Запустить*

* * *

    7. Как запустить код в режиме отладки?

Принцип запуска кода в режиме отладки не сильно отличается от запуска без отладки:

* Нажатием _F5_
* Навигацией в левую нижнюю часть экрана и нажатию на зеленый треугольник с инонкой жука
* Отладка -> Начать отладку

![Изображение#11](Screenshots/10.png "Рис. 11")\
*Рис.11 Запуск с отладкой через вкладку в верхей части экрана*

![Изображение#12](Screenshots/27.png "Рис. 12")\
*Рис.12 Альтернативный способ запустить отладку*

* * *

    8. Как установить/убрать точку остановки (breakpoint)?

Установить и убрать точку остановки можно нажатием на небольшую вертикальную секцию слева от кода и счетчика строк (Рисунок 15)

![Изображение#13](Screenshots/12.png "Рис. 13")\
*Рис.13 Установка брейкпойнта*

* * *

    Пункт №9

Я создал программу (Рисунки 16 и 19) с необходимым кодом и выполнил подзадачи.

Результатом оказалось, что в обоих случаях на пятой строчке в этих переменных лежал "мусор" из памяти (Рисунки 17 и 19), которая была для них выделена, но на шестой строчке (после операции присваивания) значение становилось равным 5 (Рисунки 18 и 20)

![Изображение#14](Screenshots/13.png "Рис. 14")\
*Рис.14 Переведённый редактор в режим отладки;*

![Изображение#15](Screenshots/28.png "Рис. 15")\
*Рис.15 Значение i на пятой строчке*

![Изображение#16](Screenshots/29.png "Рис. 16")\
*Рис.16 Значение d на шестой строчке*

![Изображение#17](Screenshots/30.png "Рис. 17")\
*Рис.17 Значение i и d на седьмой строчке*

Эти значения не совпадают с теми, что я получал в MSVS, так как и там и там переменные изнально были инициализированны мусором из памяти

* * *

    Пункты №10-17

![Изображение#18](Screenshots/18.png "Рис. 18")\
*Рис.18 Нужный нам проект из примеров*

![Изображение#19](Screenshots/19.png "Рис. 19")\
*Рис.19 Выбор комплекта сборки*

![Изображение#20](Screenshots/20.png "Рис. 20")\
*Рис.20 Запускаем проект (производим сборку)*

![Изображение#21](Screenshots/21.png "Рис. 21")\
*Рис.21 Вызванная справка от F1*

![Изображение#22](Screenshots/22.png "Рис. 22")\
*Рис.22 Открытая форма "calculatorform.ui"*

![Изображение#23](Screenshots/31.png "Рис. 23")\
*Рис.23 Меняем язык путём прописывания нового значения*

![Изображение#24](Screenshots/23.png "Рис. 24")\
*Рис.24 Итоговая форма*

* * *

## Вывод

Я изучил основные возможности создания и отладки программ в IDE Qt Creator. Сравнил работу отладчика Qt Creator с отладчиком Visual Studio. Научился менять базовые параметры визуальных компонентов в редакторе дизайна.