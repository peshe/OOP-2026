
struct Sieve;

// създава сито с размер n (заделя памет и инициализира стойностите)
Sieve * createSieve(size_t n);

// освобождава паметта за ситото sieve
void destroySieve(Sieve * s);


// селектор
bool get(Sieve * s, size_t k);

// мутатор
void set(Sieve * s, size_t k, bool b);

// връща индекс на първия елемент със стойност True
// намиращ се след start
// или size_t(-1) ако няма такъв
size_t firstTrue(Sieve * s, size_t start);
size_t firstFalse(Sieve * s, size_t start;