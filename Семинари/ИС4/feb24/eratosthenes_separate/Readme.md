# Пример за разделна компилация

Разделяме примерът за ситото на Ератостен на две части - frontend в `eratosthenesFE.cpp` и backend в `eratosheneseBE.cpp`


Функцията first_false от `eratosheneseBE.cpp` не е предназначена за употреба от друго място и затова сме я маркирали като `static`

Функцията `eratosthenes` в същия файл е предназначена за употреба от друго място и затова сме написали нейна декларациа (прототип) в заглавния файл `eratosheneseBE.h`

Този файл се *включва* в `eratosthenesFE.cpp` чрез `#include`
