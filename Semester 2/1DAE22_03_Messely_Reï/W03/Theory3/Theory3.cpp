#include "pch.h"
#include <iostream>
#include "DAEStudent.h"

int main()
{
    std::cout << "Hello World!\n";
    DAEStudent* randomStudent{ new DAEStudent{"Re�","Messely",DAEStudent::Major::GD} };

    randomStudent->Identify();

    delete randomStudent;
    randomStudent = nullptr;
}