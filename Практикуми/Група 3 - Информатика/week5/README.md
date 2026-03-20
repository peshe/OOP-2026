# Седмица 5 — Шаблони (Templates) със Структури

> **Правила:** Всяка задача изисква поне един шаблон

---

## Задача 1 — Лесна: Шаблонна двойка

Създайте шаблонна структура `Pair<T, U>` с две стойности от евентуално различни типове.

- `void swap(Pair<T,T>&)` — разменя двете стойности (само за еднакви типове).
- `void print(const Pair<T,U>&)` — извежда `(first, second)`.

---

## Задача 2 — Лесна: Шаблонен масив с фиксиран размер

Създайте шаблонна структура `Array<T, N>`, която обвива C-масив с фиксиран размер `N`.

- `bool at(Array<T, N>& arr, size_t index, T& out)` — достъп с проверка на граници.
- `size_t size(const Array<T, N>& arr) const`
- `Array<T, N> fill(const T& value)`

---

## Задача 3 — Лесна: Побитово броене

Шаблонна функция `usngined int countBits<T>(T value)` — брои единичните битове без вградени функции.

Структура `BitStats` съдържа: брой единици, брой нули, позиция на MSB.

Функция `BitStats analyze(T value)` попълва структурата.

---

## Задача 4 — Средна: Точка в N-мерно пространство

Шаблонна структура `Point<T, N>`.

- `void add(const Point&, const Point&, Point&)` и `sub` — събиране/изваждане.
- `T dot(const Point&) const` — скаларно произведение.
- `double norm(const Point&) const` — евклидова норма.

---

## Задача 5 — Средна: Побитова маска

Шаблонна структура `BitMask<T>`:

- `void set(BitMask<T>&, int pos)`, `void clear(BitMask<T>&, int pos)`, `void toggle(BitMask<T>&, int pos)`, `bool test(const BitMask<T>&, int pos) const`, `T value(const BitMask<T>&) const`
- Функция `merge(BitMask<T> a, BitMask<T> b, T mask)` — взима битовете от `a` там където `mask` е 1, от `b` другаде.

---

## Задача 6 — Средна: Крайна група ℤ/nℤ

Шаблонна структура `Zn<int N>` — елемент от адитивната група по модул `N`.

- Функции `add`, `sub`, `mul` (с редукция по модул `N`).
- `Zn<N> inverse(const Zn<N>&)` — адитивна инверсия.
- `int order(const Zn<N>&)` — ред на елемента в адитивната група.
- `bool isGenerator(const Zn<N>&)` — дали елементът генерира цялата група.

---

## Задача 7 — Трудна: Шаблонна матрица

Шаблонна структура `Matrix<T, Rows, Cols>` с методи `get`, `set`, `print`.

- Функции `add` и `multiply` (размерите се проверяват с `static_assert`).
- `Matrix<T,C,R> transpose(const Matrix<T,R,C>&)`
- За квадратни матрици: `T trace(const Matrix<T,N,N>&)` и `Matrix<T,N,N> identity()`.
