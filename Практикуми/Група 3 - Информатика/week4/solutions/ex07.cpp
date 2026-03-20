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

Student* findMaxGpa(std::fstream& file, int total) {
    Student* best = readStudentAt(file, 0);
    if (!best) {
        std::cerr << "Error reading first student.\n";
        return nullptr;
    }
    for (int i = 1; i < total; i++) {
        Student* s = readStudentAt(file, i);
        if (!s) {
            std::cerr << "Error reading student at index " << i << ".\n";
            continue;
        } else if (s->gpa > best->gpa){
            delete best;
            best = s;
        }
        else {
            delete s;
        }
    }
    return best;
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
    Student* best = findMaxGpa(file, total);
    if (best) {
        std::cout << "Студент с най-висок GPA: " << best->name << "  " << best->age << "  " << best->gpa << "\n";
        delete best;
    }
    file.close();
    return 0;
}
