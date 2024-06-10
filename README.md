# s21_containers

Реализация библиотеки s21_containers.h.
Основные стандартные контейнерные классы языка С++: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек) и `vector` (вектор). + еще несколько не так часто используемых, но отличающихся деталями реализации контейнерных классов из контейнерной библиотеки C++.

## Contents

1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-реализация-библиотеки-s21_containersh)  
   3.2. [Part 2](#part-2-дополнительно-реализация-библиотеки-s21_containersplush)  
   3.3. [Part 3](#part-3-дополнительно-реализация-методов-insert_many)

## Introduction

-   Код программы должен находиться в папке src
-   При написании кода необходимо придерживаться Google Style
-   Обязательно использовать итераторы
-   Классы обязательно должны быть шаблонными
-   Классы должны быть реализованы внутри пространства имен `s21`
-   Полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest
-   Запрещено копирование реализации стандартной библиотеки шаблонов (STL)
-   Необходимо соблюсти логику работы стандартной библиотеки шаблонов (STL) (в части проверок, работы с памятью и поведения в нештатных ситуациях)

### Part 1. Реализация библиотеки s21_containers.h

Реализованы классы библиотеки `s21_containers.h` (спецификации указаны в соответствующих разделах материалов, см. пункт **"Основные контейнеры"**). \
Список классов: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).

-   Решение в виде заголовочного файла `s21_containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_list.h`, `s21_map.h` и т.д.)
-   Makefile для тестов написанной библиотеки (с целями clean, test)
-   За основу рассмотрена классическая реализацию контейнеров. За исключением списка - реализовыван через структуру списка, а не через массив.

### Part 2. Дополнительно. Реализация библиотеки s21_containersplus.h

Реализованы функции библиотеки `s21_containersplus.h` (спецификации указаны в соответствующих разделах материалов, см. пункт **"Дополнительные контейнеры"**). \
Список классов, которые реализованы дополнительно: `array` (массив), `multiset` (мультимножество).

-   Решение в виде заголовочного файла `s21_containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_array.h`, `s21_multiset.h`)
-   Предусмотреть Makefile для тестов написанной библиотеки (с целями clean, test)

### Part 3. Дополнительно. Реализация методов `insert_many`

Дополнены классы соответствующими методами, согласно таблице:

| Modifiers                                                      | Definition                                                    | Containers          |
| -------------------------------------------------------------- | ------------------------------------------------------------- | ------------------- |
| `iterator insert_many(const_iterator pos, Args&&... args)`     | inserts new elements into the container directly before `pos` | List, Vector        |
| `void insert_many_back(Args&&... args)`                        | appends new elements to the end of the container              | List, Vector, Queue |
| `void insert_many_front(Args&&... args)`                       | appends new elements to the top of the container              | List, Stack         |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)` | inserts new elements into the container                       | Map, Set, Multiset  |

В качестве аргументов передаются уже созданные элементы соответствующего контейнера, которые необходимо вставить в этот контейнер.
