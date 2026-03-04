#include <fstream>
#include <iostream>

struct Student {
    int fn;
    char name[32];
    double grade;

    // Helper function for printing
    void print() const {
        std::cout << "FN: " << fn
            << " | Name: " << name
            << " | GPA: " << grade << std::endl;
    }
};

// Function to save an object to a file
void saveStudent(const char* filename, const Student& s) {
    // Open in append mode to add data without deleting existing records
    std::ofstream out(filename, std::ios::app);

    if (!out) return;

    // We use '\t' to ensure names with spaces (e.g., "Ivan Ivanov")
    // don't break the formatting
    out << s.fn << "\t" << s.name << "\t" << s.grade << "\n";

    out.close();
}

// Function to read and reconstruct objects
void loadAndPrintStudents(const char* filename) {
    std::ifstream in(filename);

    if (!in) {
        std::cerr << "Error reading file." << std::endl;

        return;
    }

    Student temp;
    std::cout << "--- DATA ---" << std::endl;

    while (in >> temp.fn) {
        // Skips the '\t' sitting right after the FN (if we don't skip it,
        // 'getline()' would see the tab as the first char and stop immediately)
        in.ignore();

        // Read the name until the NEXT tab
        in.getline(temp.name, 32, '\t');

        // Read the grade
        in >> temp.grade;

        // Clean up the remaining newline so it doesn't interfere
        // with the next loop iteration
        in.ignore(1000, '\n');

        temp.print();
    }

    in.close();
}

int main() {
    const char* db = "students_db.txt";

    Student s1 = { 12345, "Ivan Ivanov", 5.50 };
    Student s2 = { 55555, "Maria Petrova", 6.00 };

    // Serialize students (save them to disk)
    saveStudent(db, s1);
    saveStudent(db, s2);

    // Deserialize students (read them back as objects)
    loadAndPrintStudents(db);

    return 0;
}