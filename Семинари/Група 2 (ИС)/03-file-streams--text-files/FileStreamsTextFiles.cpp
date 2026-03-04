#include <iostream>
#include <fstream>

void printNum(int asdf)
{
    std::cout << "Int :" << asdf;
}

void printNum(double asdf)
{
    std::cout << "double :" << asdf;
}

int main()
{
    // printNum(5);

    // std::cout << "Hello World!\n";

    // ostream (output stream), like std::cout
    // istream (input stream), like std::cin

    //
    // Absolute paths
    //
    // Unix (MacOS/Linux)
    //   '/' -> root
    // Example: /Users/alex/Downloads/seminar-2.pdf
    //
    // Windows
    // Example: C:\Users\alex\Downloads\seminar-2.pdf
    //
    // Relative path:
    //   relative to what?
    //


    const char filePath[] = "someDir/testfile5.txt";
    // std::fstream stream(filePath, std::ios::in | std::ios::out | std::ios::trunc);

    // За писане във файл използваме обект от тип std::ofstream (output file stream)

    /// Както и работата с динамична памет, работата с файлове изисква 4 стъпки

    // 1) Отваряне на файл
    std::ofstream out(filePath, std::ios::app);

    // 2) Проверка дали сме успели да отворим файла
    if (!out)
    {
        std::cout << "File not found!\n";
        return -1;
    }

    // 3) Използване на файла
    out << "Hello!\n";

    // 4) Затварне на файла
    out.close();

    // За четене от файл използваме обект от тип std::ifstream (input file stream)

    const int bufferSize = 30;
    char buffer[bufferSize] = {};  // Буфер, в който ще записваме прочетеното
    std::ifstream in(filePath);
    if (!in)
    {
        std::cout << "File not found!\n";
        return -1;
    }

    char ch = in.peek();  // Поглежда следващия символ без да го взима
    char ch2 = in.get();  // Взима следващия символ
    std::cout << ch << "\n";
    std::cout << ch2 << "\n";

    // Прочитане на файл до края
    // do
    // {
    //     in >> str;
    //     std::cout << str << "\n";
    // } while (!in.eof());

    while (in >> buffer)
        std::cout << buffer << "\n";

    in.close();

    return 0;
}
