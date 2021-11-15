#include "pch.h"
#include <iostream>
#include <chrono>
#include <string>

#pragma region 4.1.1
int Sum(int val1, int val2);
#pragma endregion
#pragma region 4.1.2
void Print(int value, char delimiter);
void Print(char value, char delimiter);
void Print(float value, char delimiter);
void TestPrint();
#pragma endregion
#pragma region 4.1.3
void TestMultiply();
void TestPrintNumbers();
void TestCalcElapsedTime();
void TestPrintMessage();
void TestIsEven();
void TestIsLeap();
void TestGetIntRand();
void TestGetFloatRand();
void TestGetDistance();
void TestCalcCosSin();

int Multiply(int val1, int val2);
int Modulo(int number, int divisor);
void PrintNumbers(int start, int end);
void CalcElapsedTime(int start, int end);
void PrintMessage(std::string message, int indentations = 0);
bool IsEven(int number);
bool IsLeapYear(int year);
int GetRand(int minValue, int maxValue);
float GetRand(float minValue, float maxValue);
#pragma endregion

int main()
{
   /* Sum(50, 30);
    Sum(40, 20);
    Sum(70, 100);
    TestPrint();
    TestMultiply();*/
    //TestPrintNumbers();
    //TestCalcElapsedTime();
    //TestPrintMessage();
    //TestIsEven();
    //TestIsLeap();
    TestGetIntRand();
    TestGetFloatRand();
}
#pragma region 4.1.1
int Sum(int val1, int val2)
{
    std::cout << val1 << " + " << val2 << std::endl;
    return val1 + val2;
}
#pragma endregion
#pragma region 4.1.2
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
void TestPrint()
{
    Print('a', ',');
    Print(20, ',');
    Print(20.0f, ',');
}
#pragma endregion
#pragma region 4.1.3
void TestMultiply()
{
    std::cout << "~ Function that calculates the product of 2 integers ~\n";
    int n1{}, n2{}, n3{}, n4{};
    std::cout << "Please enter 2 numbers to multiply.\n";
    std::cout << "Number 1? ";
    std::cin >> n1;
    std::cout << "Number 2? ";
    std::cin >> n2;
    std::cout << Multiply(n1, n2) << std::endl;
    std::cout << "Please enter 4 numbers to multiply.\n";
    std::cout << "Number 1? ";
    std::cin >> n1;
    std::cout << "Number 2? ";
    std::cin >> n2;
    std::cout << "Number 3? ";
    std::cin >> n3;
    std::cout << "Number 4? ";
    std::cin >> n4;
    std::cout << Multiply(Multiply(n1, n2), Multiply(n3, n4));
}
void TestPrintNumbers() 
{
    std::cout << "~ Function that prints the integers in a given interval ~\n";
    std::cout << "Interval [10,20]\n";
    PrintNumbers(10, 20);
    std::cout << std::endl;
    std::cout << "Interval [90,115]\n";
    PrintNumbers(90, 115);
    std::cout << std::endl;
}
void TestCalcElapsedTime()
{
    std::cout << "~ Function that counts the time of printing a task ~\n";
    std::cout << "Interval [0,30]\n";
    CalcElapsedTime(0, 30);
    std::cout << "\nInterval [0,400]\n";
    CalcElapsedTime(0, 400);
}
void TestPrintMessage() 
{
    PrintMessage("No indention specified");
    std::cout << std::endl;
    PrintMessage("2 spaces indention specified", 2);
    std::cout << std::endl;
    PrintMessage("4 spaces indention specified", 4);
    std::cout << std::endl;
}
void TestIsEven()
{
    std::cout << "~ Function that checks wheter a number is even ~\n";
    std::cout << "41 is ";
    if (IsEven(41)) 
    {
        std::cout << "even";
    }
    else 
    {
        std::cout << "odd";
    }
    std::cout << std::endl;
    std::cout << "18467 is ";
    if (IsEven(18467))
    {
        std::cout << "even";
    }
    else
    {
        std::cout << "odd";
    }
    std::cout << std::endl;
    std::cout << "6334 is ";
    if (IsEven(6334))
    {
        std::cout << "even";
    }
    else
    {
        std::cout << "odd";
    }
    std::cout << std::endl;
    std::cout << "26500 is ";
    if (IsEven(26500))
    {
        std::cout << "even";
    }
    else
    {
        std::cout << "odd";
    }
    std::cout << std::endl;
    std::cout << "19169 is ";
    if (IsEven(19169))
    {
        std::cout << "even";
    }
    else
    {
        std::cout << "odd";
    }
    std::cout << std::endl;
}
void TestIsLeap() 
{
    std::cout << "~ Function that checks if year is leap ~\n";
    int answer{};
    do 
    {
        std::cout << "Year? ";
        std::cin >> answer;
        if (answer != -1) 
        {
            std::cout << answer << " has ";
            if (IsLeapYear(answer)) 
            {
                std::cout << "29";
            }
            else 
            {
                std::cout << "28";
            }
            std::cout << " days in February\n";
        }
    } while (answer != -1);

}
void TestGetIntRand()
{
    std::cout << "~ Function that generates a random number in a given integer interval ~\n";
    std::cout << "In [1,6] " << GetRand(1, 6) << std::endl;
    std::cout << "In [10,20] " << GetRand(10, 20) << std::endl;
    std::cout << "In [-5,0] " << GetRand(-5, 0) << std::endl;
    std::cout << std::endl;
}
void TestGetFloatRand()
{
    std::cout << "~ Function that generates a random number in a given integer interval ~\n";
    std::cout << "In [0,3.14159] " << GetRand(0.0f, float(3.14159)) << std::endl;
    std::cout << "In [-2,3] " << GetRand(-2.0f, 3.0f) << std::endl;
}

int Multiply(int val1, int val2) 
{
    return val1 * val2;
}
int Modulo(int number, int divisor) 
{
    return number - ((number / divisor)* divisor);
}
void PrintNumbers(int start, int end) 
{
    for (int i{start}; i <= end; i++) 
    {
        std::cout << i << " ";
    }
}
void CalcElapsedTime(int start, int end) 
{
    std::chrono::steady_clock::time_point startTime{ std::chrono::steady_clock::now() };
    PrintNumbers(start, end);
    std::chrono::steady_clock::time_point endTime{ std::chrono::steady_clock::now() };
    std::chrono::duration<float, std::milli> elapsedTime = endTime - startTime;
    std::cout << std::endl;
    std::cout << "This print task took " << elapsedTime.count() << " milliseconds" << std::endl;
}
void PrintMessage(std::string message, int indentations)
{
    for (int i{}; i < indentations; i++) 
    {
        std::cout << " ";
    }
    std::cout << message;
}
bool IsEven(int number)
{
    return !bool(number % 2);
}
bool IsLeapYear(int year)
{
    if (year % 4 == 0) 
    {
        if (year % 100 == 0) 
        {
            if (year % 400 == 0) 
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}
int GetRand(int minValue, int maxValue)
{
    int random{};
    random = (rand() % (maxValue + 1 - minValue) + minValue);
    return random;
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
#pragma endregion

