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

bool mergeFiles(std::fstream& fileA, std::fstream& fileB, std::fstream& merged) {
    if (!fileA || !fileB || !merged) {
        std::cerr << "Error opening files.\n";
        return false;
    }
    int totalA = countStudents(fileA);
    int totalB = countStudents(fileB);
    int minCount = totalA < totalB ? totalA : totalB;

    for (int i = 0; i < minCount; i++) {
        Student* a = readStudentAt(fileA, i);
        Student* b = readStudentAt(fileB, i);

        if (!a && !b) {
            std::cerr << "Error reading students at index " << i << ".\n";
            return false;
        }
        if (!a) {
            std::cerr << "Error reading students at index " << i << ".\n";
            delete b;
            return false;
        }
        if (!b) {
            std::cerr << "Error reading students at index " << i << ".\n";
            delete a;
            return false;
        }

        std::cout << "Запис от A на позиция " << merged.tellp() << " байта\n";
        writeStudentToFile(merged, *a);

        std::cout << "Запис от B на позиция " << merged.tellp() << " байта\n";
        writeStudentToFile(merged, *b);
        delete a;
        delete b;
    }

    std::fstream& larger = totalA > totalB ? fileA : fileB;
    int maxCount = totalA > totalB ? totalA : totalB;

    for (int i = minCount; i < maxCount; i++) {
        Student* s = readStudentAt(larger, i);
        if (!s) {
            std::cerr << "Error reading student at index " << i << ".\n";
            continue;
        }
        std::cout << "Запис на остатък на позиция " << merged.tellp() << " байта\n";
        writeStudentToFile(merged, *s);
        delete s;
    }

    return true;
}

int main() {
    Student groupA[3] = {
        {"Alice", 20, 3.80f},
        {"Carol", 21, 3.95f},
        {"Eva",   20, 3.60f}
    };
    Student groupB[3] = {
        {"Bob",   22, 3.50f},
        {"Dave",  23, 2.75f},
        {"Frank", 24, 3.70f}
    };

    std::fstream fileA("groupA.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    for (const auto& s : groupA)
        writeStudentToFile(fileA, s);

    std::fstream fileB("groupB.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    for (const auto& s : groupB)
        writeStudentToFile(fileB, s);

    std::fstream merged("merged.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    mergeFiles(fileA, fileB, merged);

    std::cout << "\nСъдържание на merged.bin:\n";
    int total = countStudents(merged);
    for (int i = 0; i < total; i++) {
        Student* s = readStudentAt(merged, i);
        std::cout << s->name << "  " << s->age << "  " << s->gpa << "\n";
        delete s;
    }

    fileA.close();
    fileB.close();
    merged.close();
    return 0;
}
