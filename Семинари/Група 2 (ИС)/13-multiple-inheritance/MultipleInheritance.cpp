#include <iostream>

class IPrintable
{
public:
    virtual ~IPrintable() = default;
    virtual void Print() const = 0;
};

class IAddable
{
public:
    virtual ~IAddable() = default;
    virtual void Add(int value) = 0;
};

class Person : public IPrintable, public IAddable  // Can inherit as many classes as needed
{
public:
    ~Person() override = default;
    void Print() const override { std::cout << "Person " << age << "\n"; }
    void Add(int age) override { this->age += age; };

    int age = 0;
};

class ITeachable
{
public:
    virtual ~ITeachable() = default;
    virtual void Teach(const char* lesson) = 0;
};

class Student : public Person, public ITeachable
{
public:
    void Teach(const char* lesson) override
    {
        std::cout << "Student has been taught " << lesson << "\n";
    }
};

class Dog : public ITeachable
{
public:
    void Teach(const char* lesson) override
    {
        std::cout << "Dog has been taught " << lesson << "\n";
    }
};

class Assistant : public Student
{
};

class Weird : public Student, public Dog
{
public:
    void Teach(const char* lesson) override
    {
        Dog::Teach(lesson);
        Student::Teach(lesson);
        std::cout << "sth else \n";
    }
};

void Print(const IPrintable& printable)
{
    printable.Print();
}

void Add(IAddable& addable)
{
    addable.Add(10);
}

struct Meal
{
    int calories = 0;

    void SetCalories(int newCalories) { calories = newCalories; }
};

struct Menu
{
    struct ProxyMeal
    {
        Meal* meal;
        Menu* menu;

        void SetCalories(int newCalories)
        {
            menu->totalCalories -= meal->calories;
            meal->SetCalories(newCalories);
            menu->totalCalories += newCalories;
        }

        operator Meal&() { return *meal; }
        operator const Meal&() { return *meal; }
    };

    Meal arr[20];
    int cnt = 0;
    int totalCalories = 0;

    void AddMeal(const Meal& meal)
    {
        arr[cnt++] = meal;
        totalCalories += meal.calories;
    }

    ProxyMeal operator[](int index)
    {
        ProxyMeal res;
        res.meal = &arr[index];
        res.menu = this;
        return res;
    }

    //int TotalCalories()
    //{
    //    int totalCalories = 0;
    //    for (int i = 0; i < 20; ++i)
    //        totalCalories += arr[i].calories;
    //    return totalCalories;
    //}
};

int main()
{
    Menu menu;
    menu.AddMeal(Meal{100});
    menu.AddMeal(Meal{200});
    menu[0].SetCalories(1000);
    std::cout << menu.totalCalories;

    //std::cout << "Hello Virtual Inheritance" << std::endl;
    //
    //Person p;
    //Add(p);
    //Print(p);
    //
    //Student s;
    //Print(s);
    ////s.Teach("oop");
    //
    //Dog d;
    ////d.Teach("fetch");
    //
    //Weird w;
    //w.Teach("test");
    //
    //Assistant a;
    //a.Teach("opo");
    //
    //ITeachable* arr[] = {&s, &d};
    //const int size = 2;
    //for (int i = 0; i < size; i++)
    //    arr[i]->Teach("sth");

    return 0;
}