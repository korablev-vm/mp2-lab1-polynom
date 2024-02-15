﻿# Техническое задание для проекта "Алгебра полиномов"
## Введение

### Назначение
Техническое задание направлено на разработку программной системы для выполнения алгебраических операций над полиномами от трех переменных.

### Цели проекта
- Разработка программной системы, позволяющей эффективно работать с полиномами.
- Обеспечение выполнения основных математических операций над полиномами.

## Общие сведения

### Участники проекта
Калякина Анастасия, 
Кораблев Владлен,
Шведова Виталина

### Длительность проекта
Проект продлится 8 недель весеннего семестра.

## Функциональные требования

### Хранение полиномов
- **Полиномы хранятся в виде списка:** Система должна предусматривать хранение полиномов в структурированном виде списка, где каждый элемент списка представляет собой отдельный член полинома с коэффициентами и степенями переменных.
- **Единое хранилище в различных таблицах:** Полиномы должны быть доступны для хранения в шести различных типах таблиц одновременно. Это обеспечивает гибкость в выборе структуры данных в зависимости от конкретной задачи и оптимизации производительности операций с полиномами.

### Таблицы
- **Разнообразие структур данных.** Разработка должна включать следующие виды таблиц:
  - **Линейная таблица на массиве.** 
  - **Линейная таблица на списке.** 
  - **Упорядоченная таблица на массиве.** 
  - **Дерево (АВЛ или красно-черное).** 
  - **Две хеш-таблицы.**

### Операции над полиномами
- **Вычисление полинома в точке:** Программа должна поддерживать подстановку значений переменных и вычисление результата полинома.
- **Сложение и вычитание полиномов:** Разработка метода получения суммы и разности полиномов
- **Умножение на константу:** Полином может быть умножен на числовую константу, что приводит к умножению всех его коэффициентов на эту константу.
- **Умножение полиномов:** Создание метода, получающего произведение полиномов.


### Операции в выражениях из полиномов
- **Сложение, вычитание, умножение на константу, умножение и деление полиномов:** Эти операции должны быть реализованы таким образом, чтобы поддерживать композицию полиномов в алгебраических выражениях, используя постфиксную форму записи для обработки выражений.

### Операции над таблицами
- **Добавление и удаление полинома:** Пользователь должен иметь возможность добавлять новый полином или удалять существующий, причем изменения должны отражаться сразу во всех таблицах.
- **Поиск полинома:** Поиск должен осуществляться только в активно выбранной пользователем таблице. Это включает в себя поиск по имени полинома в процессе вычисления алгебраических выражений.
- **Вывод на экран активной таблицы:** Выбранная пользователем таблица должна выводиться на экран в формате, как минимум, двух столбцов: имя полинома и его строковое представление.

## Этапы и сроки выполнения проекта

### Этапы разработки
1. Формирование ТЗ.
2. Анализ и проектирование системы.
3. Реализация и тестирование.
4. Сдача проекта.

### Сроки
- Проект должен быть завершен за 8 недель.
