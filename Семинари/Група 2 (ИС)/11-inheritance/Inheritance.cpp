#include <iostream>

#include "Student.h"

// Overloads
int fun(int a) { return 1; }
String fun(float a) { return "overload"; }

int main()
{
    fun(5.0f);

    Person person("Tosho", 21);
    person.Print();
    std::cout << std::endl;

    Student st("Gosho", 20, "0MI12324");
    st.Print();
    std::cout << std::endl;

    Student st2(person, "1MI9084314");
    // Student st3(Person{"Georgi", 20}, "1MI9084314");  // also works

    // person.SomeUtilityMethod();  -- protected in Person, non-accessible from here
    st.SomeUtilityMethod();  // publicly overridden in Student

    Person p2 = st2;  // Downcast - ok, by default
    Student st4 = p2;  // Upcast - Can't do it by default

    Person* pPerson = &st2;
    pPerson->Print();
    std::cout << std::endl;

    // Student* pStudent = &p2;  // Can't do it by default

    std::cout << st.GetName() << std::endl;  // Can use Person's public methods

    return 0;
}
