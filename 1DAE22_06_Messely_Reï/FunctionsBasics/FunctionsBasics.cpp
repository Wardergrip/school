#include "pch.h"
#include <iostream>
#include <chrono>

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
void TestGetDistance();
void TestCalcCosSin();

int Multiply(int val1, int val2);
int Modulo(int number, int divisor);
void PrintNumbers(int start, int end);
float CalcElapsedTime(int start, int end);

#pragma endregion

int main()
{
   /* Sum(50, 30);
    Sum(40, 20);
    Sum(70, 100);
    TestPrint();
    TestMultiply();*/
    TestPrintNumbers();
    
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
float CalcElapsedTime(int start, int end) 
{
    std::chrono::steady_clock::time_point startTime{ std::chrono::steady_clock::now() };
    PrintNumbers(start, end);
    
}
#pragma endregion

