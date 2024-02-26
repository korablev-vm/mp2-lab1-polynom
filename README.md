# Проект "Алгебра полиномов"
## Техническое задание
### Введение

#### Назначение
Техническое задание направлено на разработку программной системы для выполнения алгебраических операций над полиномами от трех переменных.

#### Цели проекта
- Разработка программной системы, позволяющей эффективно работать с полиномами.
- Обеспечение выполнения основных математических операций над полиномами.

### Общие сведения

#### Участники проекта
Калякина Анастасия, 
Кораблев Владлен,
Шведова Виталина

#### Длительность проекта
Проект продлится 8 недель весеннего семестра.

### Функциональные требования

#### Хранение полиномов
- **Полиномы хранятся в виде списка:** Система должна предусматривать хранение полиномов в виде списка, где каждый элемент списка представляет собой моном с коэффициентом и степенями переменных.
- **Единое хранилище в различных таблицах:** Полиномы должны быть доступны для хранения в шести различных типах таблиц одновременно. Это обеспечивает гибкость в выборе структуры данных в зависимости от конкретной задачи и оптимизации производительности операций с полиномами.

#### Таблицы
- **Разнообразие структур данных.** Разработка должна включать следующие виды таблиц:
  - **Линейная таблица на массиве.** 
  - **Линейная таблица на списке.** 
  - **Упорядоченная таблица на массиве.** 
  - **Дерево (АВЛ или красно-черное).** 
  - **Две хеш-таблицы.**

#### Операции над полиномами
- **Вычисление полинома в точке:** Программа должна поддерживать подстановку значений переменных и вычисление результата полинома.
- **Сложение и вычитание полиномов:** Разработка метода получения суммы и разности полиномов
- **Умножение на константу:** Полином может быть умножен на числовую константу, что приводит к умножению всех его коэффициентов на эту константу.
- **Умножение полиномов:** Создание метода, получающего произведение полиномов.


#### Требования к операциям над полиномами
- Операции должны быть реализованы таким образом, чтобы поддерживать композицию полиномов в алгебраических выражениях, используя постфиксную форму записи для обработки выражений.

###### Пример композиции полиномов
Допустим, имеются следующие полиномы:
- $P_1(x, y, z) = 2x^2 + yz$
- $P_2(x, y, z) = 3xy - z^2$

И пользователь хочет получить новый полином P_new, который представляет собой сумму удвоенного P1 и трехкратного P2, выражение для которого выглядит следующим образом:
$P_{new} = 2 * P_1 + 3 * P_2$

В постфиксной форме это выражение будет записано как:
$P_1 2 * P_2 3 * +$

Это означает, что сначала к $P_1$ применяется умножение на 2, к $P_2$ применяется умножение на 3, после чего результаты этих операций суммируются для получения $P_{new}$.


#### Операции над таблицами
- **Добавление и удаление полинома:** Пользователь должен иметь возможность добавлять новый полином или удалять существующий, причем изменения должны отражаться сразу во всех таблицах.
- **Поиск полинома:** Поиск должен осуществляться только в активно выбранной пользователем таблице. Это включает в себя поиск по имени полинома в процессе вычисления алгебраических выражений.
- **Вывод на экран активной таблицы:** Выбранная пользователем таблица должна выводиться на экран в формате, как минимум, двух столбцов: имя полинома и его строковое представление.

### Этапы и сроки выполнения проекта

#### Этапы разработки
1. Формирование ТЗ.
2. Анализ и проектирование системы.
3. Реализация и тестирование.
4. Сдача проекта.

#### Сроки
- Проект должен быть завершен за 8 недель.

## Список объектов и основных алгоритмов

### Объекты
- `List<T>`: Обобщённый класс списка, предназначенный для хранения элементов. Поддерживает операции вставки, удаления и доступа к элементам.
- `Monom`: Класс, представляющий моном (одночлен), с коэффициентами и степенями переменных.
- `Polinom`: Класс для представления полинома, состоящего из списка мономов.
- `Operations`: Класс с операциями для постфиксной формы.
- `TPostfix`: Класс для преобразования инфиксных выражений в постфиксные и их вычисления.
- `TStack<T>`: Класс, реализующий структуру данных стек, используется в `TPostfix` для преобразования и вычисления выражений.


### Основные алгоритмы
- Преобразование инфиксной формы в постфиксную.
- Вычисление значения полинома в заданной точке.
- Сложение, вычитание, умножение полиномов.
- Умножение полинома на константу.

## Описание моделей объектов

### List<T>
Класс `List` является обобщённым контейнером, предназначенным для хранения последовательности элементов. Поддерживает операции добавления (`insertInOrder`), удаления (`erase`) и доступа к элементам по индексу (`operator[]`). Основан на двусвязном списке, что позволяет эффективно добавлять и удалять элементы.

### Monom
`Monom` представляет собой одночлен, характеризующийся коэффициентом и набором переменных с их степенями. Поддерживает операции сложения (`operator+=`), умножения (`operator*=`) с другим мономом, дифференциации (`Differentiation`) и интеграции (`Integration`) по переменной. Количество переменных и размер показателя степени ограничивается только доступной памятью и максимально допустимыми размерами типов 'int' и 'string' (т.к. используется 'map').

### Polinom
Класс `Polinom` представляет полином как набор мономов (`List<Monom>`). Реализует арифметические операции над полиномами, такие как сложение (`operator+=`), умножение (`operator*=`), а также методы для дифференциации (`Differentiation`) и интеграции (`Integration`). Степень ограничивается переменной 'max_degree', по умолчанию ее рамки заданы как 0 < max_degree < 50

### Operations
`Operations` инкапсулирует набор операций, применимых к элементам типа `T`. Включает методы для проверки является ли строка операцией (`IfIsOperation`), получения приоритета операции (`GetPriority`) и выполнения операций над элементами (`Calculation`).

### TPostfix
Класс `TPostfix` используется для преобразования алгебраических выражений из инфиксной формы в постфиксную и последующего вычисления результата. Включает методы для преобразования (`ToPostfix`), проверки корректности выражения (`CheckOfExpression`) и вычисления (`Calculate`).

### TStack<T>
`TStack` реализует структуру данных стек. Поддерживает базовые операции стека: добавление элемента (`push`), удаление элемента (`pop`), получение верхнего элемента (`getTop`) и проверку на пустоту (`empty`). Используется в `TPostfix` для хранения операций при преобразовании выражений.

## Описание алгоритмов

### Преобразование инфиксной формы в постфиксную и выполнение операций
Алгоритм преобразования инфиксной формы выражений в постфиксную и последующее вычисление их значений включает в себя использование класса `Operations` для определения характеристик операций (таких как приоритет и арность) и выполнения алгебраических операций над операндами. Алгоритм:
- Определить, является ли символ операцией.
- Получить приоритет операции для корректного преобразования выражения.
- Узнать количество аргументов, необходимых для выполнения операции.
- Выполнить операцию над одним или несколькими операндами, в зависимости от типа операции.

### Вычисление значения полинома
Для вычисления значения полинома в заданной точке происходит подстановка значений переменных и последовательное выполнение арифметических операций согласно правилам алгебры.

### Арифметические операции над полиномами
- **Сложение полиномов**: Суммирует два полинома, результатом является новый полином, содержащий мономы из обоих слагаемых, при необходимости производится приведение подобных.
- **Вычитание полиномов**: Вычитает один полином из другого, аналогично сложению, но мономы второго полинома вычитаются.
- **Умножение полинома на константу**: Все коэффициенты полинома умножаются на заданное число.
- **Перемножение полиномов**: Результатом является полином, каждый моном которого получается умножением мономов исходных полиномов с последующим суммированием одинаковых мономов.

## Структуры данных (таблицы) для хранения полиномов


### Типы таблиц
- **Линейная таблица на массиве**: Использует массив для хранения полиномов. Подходит для случаев с заранее известным количеством элементов.
- **Линейная таблица на списке**: Основана на связном списке, обеспечивает гибкость в добавлении и удалении полиномов.
- **Упорядоченная таблица на массиве**: Массив, в котором полиномы хранятся в упорядоченном виде. Упрощает поиск и добавление новых полиномов с сохранением порядка.
- **Дерево (АВЛ или красно-чёрное)**: Сбалансированное бинарное дерево, обеспечивающее эффективный поиск, добавление и удаление элементов.
- **Хеш-таблицы**: Используют хеш-функцию для быстрого доступа к элементам по ключу. Могут быть реализованы с открытым хешированием или методом цепочек.

### Операции над таблицами
Для каждого типа таблицы поддерживаются следующие операции:
- **Добавление полинома**: Вставка нового полинома в таблицу.
- **Удаление полинома**: Удаление существующего полинома из таблицы.
- **Поиск полинома**: Поиск полинома в таблице по ключу.
- **Отображение активной таблицы**: Выбранная пользователем таблица должна выводиться на экран в формате, как минимум, двух столбцов: имя полинома и его строковое представление.
