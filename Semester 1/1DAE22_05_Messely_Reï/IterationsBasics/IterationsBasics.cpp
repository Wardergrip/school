// Messely Reï 1DAE22
#pragma region Includes&Defines
#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#pragma endregion
#pragma region Initialisation 
void evenNumbers();
void examScores();
void randomGuess();
void trigonometry();
void asciitable();
#pragma endregion

int main()
{
    evenNumbers();
    std::cout << "\n\n";
    examScores();
    std::cout << std::endl;
    randomGuess();
    std::cout << std::endl;
    trigonometry();
    std::cout << std::endl;
    asciitable();
}

void evenNumbers() 
{
    int i{};
    std::cout << "~ Even Numbers ~\n";
    for (i = 1; i <= 24; ++i)
    {
        switch (i % 2)
        {
        case 0:
            std::cout << i << " ";
            break;
        }
    }
    // reset
    i = 1;
    std::cout << std::endl;
    //
    while (i <= 24)
    {
        switch (i % 2)
        {
        case 0:
            std::cout << i << " ";
        default:
            ++i;
            break;
        }
    }
    // reset
    i = 1;
    std::cout << std::endl;
    //
    do
    {
        switch (i % 2)
        {
        case 0:
            std::cout << i << " ";
        default:
            ++i;
            break;
        }
    } while (i <= 24);
}
void examScores()
{
    
    std::cout << "~ Exam scores~" << std::endl;
    int input{};
    int scoreAPluss{}, scoreA{}, scoreB{}, scoreC{}, scoreD{}, scoreE{}, scoreFX{}, scoreF{};
    int totalScore{};
    std::string allData{};
    while (input != -1) 
    {
        std::cout << "Score [0,20] ? ";
        std::cin >> input;
        if ((input <= 20) && (input >= 0))
        {
            totalScore += input;
            if (allData == "")
            {
                allData = std::to_string(input);
            }
            else {
                allData = allData + ", " + std::to_string(input);
            }
            if (input <= 7) 
        {
            ++scoreF;
        }
            else if (input <= 9) 
        {
            ++scoreFX;
        }
            else if (input == 10) 
        {
            ++scoreE;
        }
            else if (input <= 12) 
        {
            ++scoreD;
        }
            else if (input <= 14) 
        {
            ++scoreC;
        }
            else if (input == 15) 
        {
            ++scoreB;
        }
            else if (input <= 17) 
        {
            ++scoreA;
        }
            else if (input <= 20)
        {
            ++scoreAPluss;
        }
        }
        else if (input != -1)
        {
            std::cout << "Wrong input! \n";
        }
    }
    std::cout << "A+: " << scoreAPluss << std::endl;
    std::cout << "A: " << scoreA << std::endl;
    std::cout << "B: " << scoreB << std::endl;
    std::cout << "C: " << scoreC << std::endl;
    std::cout << "D: " << scoreD << std::endl;
    std::cout << "E: " << scoreE << std::endl;
    std::cout << "FX: " << scoreFX << std::endl;
    std::cout << "F: " << scoreF << std::endl;
    std::cout << "Total score: " << totalScore << std::endl;
    if (allData != "") {
        std::cout << "Entered scores: " << allData << std::endl;
    }
    else 
    {
        std::cout << "Entered scores: none" << std::endl;
    }
}
void randomGuess() 
{
    std::cout << "~ Guess number ~" << std::endl;
    int input{};
    int guess{};
    unsigned int tries{};
    do {
        if (input < 0) 
        {
            std::cout << "That is an invalid number.\n";
        }
        std::cout << "Number to guess ? ";
        std::cin >> input;
    } while (input <= 0);
    while (guess != input) 
    {
        guess = rand();
        ++tries;
    }
    std::cout << "Number found after " << tries << " guesses.\n";
}
void trigonometry() 
{
    std::cout << "~ Trigonometry ~" << std::endl;
    int i{};
    std::cout << std::setw(10);
    std::cout << "Degrees";
    std::cout << std::setw(10);
    std::cout << "Radians";
    std::cout << std::setw(10);
    std::cout << "Cos";
    std::cout << std::setw(10);
    std::cout << "Sin";
    for (i = 0; i <= 180; i += 10) 
    {
        std::cout << std::endl;
        std::cout << std::setw(10);
        std::cout << i;
        std::cout << std::setw(10) << std::fixed << std::setprecision(2);
        std::cout << ((i / 360.0f) * M_PI);
        std::cout << std::setw(10);
        std::cout << cos((i / 360.0f) * M_PI);
        std::cout << std::setw(10);
        std::cout << sin((i / 360.0f) * M_PI);
    }
}
void asciitable()
{
    std::cout << "~ ASCII table ~" << std::endl;
    char i{};
    for (i = 'a'; i <= 'm'; i++) 
    {
        std::cout << std::setw(2);
        std::cout << i; 
        std::cout << std::setw(5);
        std::cout << int(i); 
        std::cout << std::setw(6);
        std::cout << char(i + 13);
        std::cout << std::setw(9);
        std::cout << (i+13);
        std::cout << std::endl;
    }
}