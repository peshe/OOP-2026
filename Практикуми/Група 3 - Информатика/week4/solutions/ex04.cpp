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

int countStudents(std::fstream& file) {
    if (!file) {
        std::cerr << "Error opening file.\n";
        return 0;
    }
    file.seekg(0, std::ios::end);
    int count = static_cast<int>(file.tellg()) / sizeof(Student);
    file.seekg(0, std::ios::beg);
    return count;
}

Student* readStudentAt(std::fstream& file, int index) {
    if (!file) {
        std::cerr << "Error opening file.\n";
        return nullptr;
    }
    if (index < 0 || index >= countStudents(file)) {
        std::cerr << "Invalid index.\n";
        return nullptr;
    }

    file.seekg(index * sizeof(Student), std::ios::beg);
    Student* s = new(std::nothrow) Student();
    if (!s) {
        std::cerr << "Error allocating memory.\n";
        return nullptr;
    }

    file.read(reinterpret_cast<char*>(s), sizeof(Student));
    if (!file) {
        std::cerr << "Error reading from file.\n";
        delete s;
        return nullptr;
    }
    return s;
}

void updateStudentGpa(std::fstream& file, int index, float newGpa) {
    if (!file) {
        std::cerr << "Error opening file.\n";
        return;
    }
    if (index < 0 || index >= countStudents(file)) {
        std::cerr << "Invalid index.\n";
        return;
    }
    if (newGpa < 0.0f || newGpa > 6.0f) {
        std::cerr << "Invalid GPA value.\n";
        return;
    }
    Student* s = readStudentAt(file, index);
    if (!s) {
        std::cerr << "Error reading student from file.\n";
        return;
    }
    s->gpa = newGpa;
    file.seekp(index * sizeof(Student), std::ios::beg);
    file.write(reinterpret_cast<const char*>(s), sizeof(Student));
    delete s;
}

int main() {
    Student students[5] = {
        {"Alice", 20, 3.80f},
        {"Bob",   22, 3.50f},
        {"Carol", 21, 3.95f},
        {"Dave",  23, 2.75f},
        {"Eva",   20, 3.60f}
    };

    std::fstream file("students.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    for (const auto& s : students)
        writeStudentToFile(file, s);

    int total = countStudents(file);

    int index;
    float newGpa;
    std::cout << "Индекс на студент за обновяване (0-" << total - 1 << "): ";
    std::cin >> index;

    if (index < 0 || index >= total) {
        std::cerr << "Невалиден индекс.\n";
        return 1;
    }

    std::cout << "Нов GPA: ";
    std::cin >> newGpa;

    updateStudentGpa(file, index, newGpa);

    file.seekg(0, std::ios::beg);
    Student s;
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student)))
        std::cout << s.name << "  " << s.age << "  " << s.gpa << "\n";

    file.close();
    return 0;
}
