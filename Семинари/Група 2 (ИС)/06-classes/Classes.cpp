#include <iostream>

// The struct is almost equivalent to a class with a public modifier
struct Structure
{
    int x = 0;
};

class Class
{
public:
    int x = 0;
};

void fun()
{
    // Static variables inside functions are created only once and
    // are initialized only once - the first time the function is called
    static int counter = 0;

    std::cout << counter++ << "\n";

    if (counter == 2)
        std::cout << "Woo!\n";
}

class Person
{
    // Everything after the `public:` modifier is called "an interface" of the class.
    // Everybody outside of this class can access everything after the `public:` modifier.
public:

    // A static variable (constant), it is initialized exactly once at the start of your program.
    // You can think of this static variable as a "global variable (constant)" for the class and
    //   NOT a variable that is inside each object.
    static const int MAX_NAME_SIZE = 10;

    // Parametrized constructor,
    // used when creating (constructing) variables (objects) of type Person
    Person(const char* newName, int newAge)
    {
        this->SetName(newName);
        this->SetAge(newAge);
    }

    // We can imagine, internally, that each function (method) of our class
    // has as a first parameter - `Person* this` or `const Person* this`.
    //
    // In the case of the Print method:
    // The keyword `this` is a pointer to a constant Person (const Person*).
    // `this` is a pointer to the object that was used to call this method.
    void Print() const  // We add `const` at the end of methods that don't change the object
    {
        std::cout << this->name << " is " << this->age << " yo\n";
    }

    // Since we don't have `const` at the end of the method declaration,
    // `this` is a Person* and we can use it to change the object's fields.
    bool SetName(const char* newName)
    {
        // Note: We do not have to explicitly use the `this` keyword
        if (strlen(newName) < MAX_NAME_SIZE)
        {
            strcpy(name, newName);
            return true;
        }

        return false;
    }

    const char* GetName() const  // `this` is a const Person*
    {
        return name;
    }

    bool SetAge(int newAge)  // `this` is a Person*
    {
        if (newAge > 0 && age < 200)
        {
            age = newAge;
            return true;
        }

        return false;
    }

    int GetAge() const
    {
        return age;
    }

private:
    char name[MAX_NAME_SIZE] = {'\0', };
    int age = 0;
};

int main()
{
    Structure str = {5};
    std::cout << str.x << "\n";

    Class cl = {5};
    std::cout << cl.x << "\n";

    fun();
    fun();
    fun();

    // Each of these call the constructor
    Person person = {"gosho", 20};
    Person person2 {"tosho", 21};
    Person person3("mosho", 22);

    if (!person.SetName("123456789123459"))
        std::cout << "Couldn't change the person's name! Too long!\n";

    person.SetAge(25);
    person.Print();

    // Since MAX_NAME_SIZE is a public static variable, we can access it like so:
    std::cout << person.MAX_NAME_SIZE << "\n";
    // or like so, without an object
    std::cout << Person::MAX_NAME_SIZE << "\n";

    // char* name = person.GetName();  // Error: not allowed to cast to a non-const char*
    // We've encapsulated our objects, and users of our class can only change
    // the objects of our class through the class's public interface (public methods)

    const char* name = person.GetName();
    std::cout << name << "\n";

    return 0;
}
