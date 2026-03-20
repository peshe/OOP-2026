#include <fstream>
#include <iostream>

struct Student {
    char  name[32];
    int   age;
    float gpa;
};

void writeStudentToFile(std::fstream& file, const Student& s) {
    if (!file){
        std::cerr << "Error opening file for writing.\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
}

std::istream &readStudent(std::fstream &file, Student &s)
{    
    if (!file) {
        std::cerr << "Error opening file for reading.\n";
        return file;
    }
    return file.read(reinterpret_cast<char *>(&s), sizeof(Student));
}


int main()
{
    Student students[5] = {
        {"Alice", 20, 3.80f},
        {"Bob",   22, 3.50f},
        {"Carol", 21, 3.95f},
        {"Dave",  23, 2.75f},
        {"Eva",   20, 3.60f}
    };

    std::fstream file("students.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    for (const auto& s : students)
        writeStudentToFile(file, s);

    if (!file) {
        std::cerr << "Error writing to file.\n";
        return 1;
    }

    file.seekg(0, std::ios::beg);
    
    if (!file) {
        std::cerr << "Error seeking in file.\n";
        return 1;
    }

    Student s;
    while (readStudent(file, s))
        std::cout << s.name << "  " << s.age << "  " << s.gpa << "\n";

    file.close();
    return 0;
}

