// Messely, Reï, 1DAE22

#include "pch.h"
#include <iostream>

void Print(int value, char delimiter = ' ');
void Print(char value, char delimiter = ' ');
void Print(float value, char delimiter = ' ');

float GetRand(float minValue, float maxValue);

void CalcCosSin(double angle, double& cosResult, double& sinResult);
void TestCalcCosSin();

int main()
{
    std::cout << "Hello World!\n";
    Print(7);
    Print('b');
    Print(1.5f);
    std::cout << std::endl;
    TestCalcCosSin();
}

void Print(int value, char delimiter)
{
    std::cout << value << delimiter;
}
void Print(char value, char delimiter)
{
    std::cout << value << delimiter;
}
void Print(float value, char delimiter)
{
    std::cout << value << delimiter;
}

float GetRand(float minValue, float maxValue)
{
    int random{};
    int min{ int(minValue * 100) };
    int max{ int(maxValue * 100) };
    random = (rand() % (max + 1 - min) + min);
    float randomFloat{ random / 100.0f };
    return randomFloat;
}

void CalcCosSin(double angle, double& cosResult, double& sinResult) 
{
    cosResult = cos(angle);
    sinResult = sin(angle);
}
void TestCalcCosSin()
{
    const double pi{ 3.14159 };
    double cosResult{}, sinResult{}, randomAngle{};
    for (int i{0}; i < 10; i++) 
    {
        randomAngle = GetRand(0, int( 2 * pi));
        CalcCosSin(randomAngle, cosResult, sinResult);
        std::cout << "RandomAngle: " << randomAngle << " Cos: " << cosResult << " Sin: " << sinResult << "\n";
    }
}