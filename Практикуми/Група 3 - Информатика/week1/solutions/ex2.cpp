bool isTriangle(int a, int b, int c) {
    // Проверка дали сумата на всеки две от страните е по-голяма от третата
    return (a + b > c) &&
             (a + c > b) &&
             (b + c > a);
}

void sumVectors(float x1, float y1, float x2,  float y2, float& x3, float& y3) {
    x3 = x1 + x2;
    y3 = y1 + y2;
    return;
}
