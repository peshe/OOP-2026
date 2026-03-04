#pragma once

const int MAX_PERSON_NAME = 50;
const int UNKNOWN_AGE = -1;

struct Person
{
    int age = UNKNOWN_AGE;            // 4 bytes
    char name[MAX_PERSON_NAME] = {};  // 50 bytes
    // 2 bytes padding for a total of 56 bytes
};

void printPerson(const Person& person);
void readPerson(Person& outPerson);

// void fun(Person* outPerson);
// void fun(const Person* person);
void fun(Person personCopy);
