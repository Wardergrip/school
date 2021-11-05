// Messely Reï - 1DAE22

#include "pch.h"
#include <iostream>

int main()
{
#pragma region O4.1.5

    int number{7};
    char symbol{'w'};
    bool isTrue{true};

    float largeNumber{420};
    double precisionNumber{3.1415f};
    std::cout << number << symbol << isTrue << largeNumber << precisionNumber << std::endl;
#pragma endregion
#pragma region O4.1.6
    number = 42;
    symbol = 'f';
    isTrue = false;

    largeNumber = 1000;
    precisionNumber = 6.28f;
    std::cout << number << symbol << isTrue << largeNumber << precisionNumber << std::endl;
#pragma endregion
#pragma region O4.1.7
    std::cout << "Age? ";
    std::cin >> number;
    std::cout << number << std::endl;
    std::cout << "First letter? ";
    std::cin >> symbol;
    std::cout << symbol << std::endl;
    std::cout << "Do you like 1 or 0 more? ";
    std::cin >> isTrue;
    std::cout << isTrue << std::endl;
    std::cout << "In what year where you born? ";
    std::cin >> largeNumber;
    std::cout << largeNumber << std::endl;
    std::cout << "How many is 5.0 / 2? ";
    std::cin >> precisionNumber;
    std::cout << precisionNumber << std::endl;
    std::cout << "To summarize, your answers were: " << number << symbol << isTrue << largeNumber << precisionNumber << std::endl;
#pragma endregion
#pragma region O4.2.1
    number = number + 7;
    std::cout << number << " ";
    largeNumber = largeNumber + number;
    std::cout << largeNumber << " ";
    symbol = symbol - 1;
    std::cout << char(symbol) << " ";
    symbol = symbol - number;
    std::cout << char(symbol) << std::endl;
#pragma endregion
#pragma region O4.2.2 + O4.2.3
    number = 10 / 2;
    std::cout << number << " ";
    largeNumber = number * 5;
    std::cout << largeNumber << " ";
    largeNumber = largeNumber / number;
    number += 1;
    std::cout << number << " ";
    std::cout << largeNumber << " ";
    int smallInteger{ 2 };
    std::cout << number / smallInteger << std::endl;
#pragma endregion
}