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

    if (!file) {
        std::cerr << "Error writing to file.\n";
        return 1;
    }
    
    int count = countStudents(file);

    std::cout << "Размер на файла: " << count * sizeof(Student) << " байта\n";
    std::cout << "Брой студенти: "   << count << "\n";

    file.close();
    return 0;
}
