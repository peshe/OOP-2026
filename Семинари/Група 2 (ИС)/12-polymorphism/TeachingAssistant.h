#pragma once
#include <iostream>

#include "Student.h"
#include "Teacher.h"


class TeachingAssistant : public Student, public Teacher
{
public:
    TeachingAssistant() = default;

    void Print() const override { std::cout << "TA\n"; }
};
