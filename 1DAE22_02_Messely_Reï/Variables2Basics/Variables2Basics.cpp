// Messely, Reï - 1DAE22

#include "pch.h"
#include <string>
#include <iostream>

void evenOrOneven();
void randomBetweenIntervals();
void asciiToValue();
void roundingVersusCasting();
void aspectRatio();
void exc3_2_5();
void ExploreStrings();

int main()
{
    srand( int ( time (nullptr)));
    evenOrOneven();
    randomBetweenIntervals();
    asciiToValue();
    roundingVersusCasting();
    aspectRatio();
    exc3_2_5();
    ExploreStrings();
}
void evenOrOneven() 
{
    int answer{};
    std::cout << "Tell me a number, and I will say if it's even! (0 = even, 1 = oneven)\n";
    std::cin >> answer;
    std::cout << answer % 2 << std::endl;
}
void randomBetweenIntervals() 
{
    std::cout << rand() % 51 << std::endl;
    std::cout << rand() % 71 + 10 << std::endl;
    std::cout << rand() % 41 - 20 << std::endl;
    std::cout << rand() % 5 - 2 << std::endl;

    std::cout << (rand() % 500 + 500) / 100.00f << std::endl;
    std::cout << (rand() % 1000 - 500) / 100.00f << std::endl;
}
void asciiToValue() 
{
    char answer{};
    std::cout << "Letter? " << std::endl;
    std::cin >> answer;
    std::cout << "Letter " << answer << ", ASCII value " << int(answer) << std::endl;
    char randomLetter = rand() % ('z' - 'a') + 'a';
    std::cout << "Random letter " << randomLetter << ", ASCII value " << int(randomLetter) << std::endl;
}
void roundingVersusCasting() 
{
    float number1{ 5.44f };
    float number2{ 5.45f };
    float number3{ 5.51f };
    std::cout << number1 << ", rounded: " << round(number1) << ", int cast: " << int(number1) << std::endl;
    std::cout << number2 << ", rounded: " << round(number2) << ", int cast: " << int(number2) << std::endl;
    std::cout << number3 << ", rounded: " << round(number3) << ", int cast: " << int(number3) << std::endl;

}
void aspectRatio() 
{
    std::cout << "The aspect ratio of full HD (1920x1080) is :" << (1920 / 1080.0f) << std::endl;
}
void exc3_2_5() 
{
    int i{ 10 };
    int j{ ++i };
    std::cout << "i: " << i << " j: " << j << std::endl;

    int k{ 10 };
    int l{ k++ };
    std::cout << "k: " << k << " l: " << l << std::endl;

}
void ExploreStrings() 
{
    char testingChar{ 'u' };
    std::string test;
    std::string answer;
    std::string answer2;
    std::cout << test << std::endl;
    test = "I am a string literal.";
    test = test + " cool!";
    std::cout << test << std::endl;
    std::cout << "First word? " << std::endl;
    std::cin >> answer;
    std::cout << "Second word? " << std::endl;
    std::cin >> answer2;
    std::cout << answer + answer2 << std::endl;
    std::cout << "Your word is " + answer + answer2 << std::endl;
    std::cout << testingChar + answer + answer2 + 'w' << std::endl;
    std::cout << "This is test number " + std::to_string(120) << std::endl;

    std::string numbersLog{};
    int enteredNr{};
    std::cout << "Enter an integer value: ";
    std::cin >> enteredNr;
    numbersLog = numbersLog + " " + std::to_string(enteredNr);
    std::cout << "Enter an integer value: ";
    std::cin >> enteredNr;
    numbersLog = numbersLog + " " + std::to_string(enteredNr);
    std::cout << "Enter an integer value: ";
    std::cin >> enteredNr;
    numbersLog = numbersLog + " " + std::to_string(enteredNr);
    std::cout << "Log of entered values:" + numbersLog << std::endl;

    std::string stringOne{ "3" };
    std::string stringTwo{ "3.1415"};
    std::cout << "String One contains " + stringOne << std::endl;
    std::cout << "String Two contains " + stringTwo << std::endl;
    std::cout << "Adding strings " + stringOne + stringTwo << std::endl;
    std::cout << "Adding numbers " << std::stoi(stringOne) + std::stof(stringTwo) << std::endl;
}