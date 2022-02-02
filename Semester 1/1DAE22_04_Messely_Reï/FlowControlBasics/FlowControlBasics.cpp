// Messely Reï 1DAE22
#include "pch.h"
#include <iostream>

void PrintTruthTable();
void CompareTwoNumbers();
void CalculatePrice();
void ConvertDayNumber();
void CheckLeapYear();
void ConvertSeconds();
void UseActorState();
void UsePoint2f();

enum class ActorState
{
    running,flying,falling
};

int main()
{
    srand(unsigned int(time(nullptr)));
    PrintTruthTable();
    CompareTwoNumbers();
    CalculatePrice();
    ConvertDayNumber();
    CheckLeapYear();
    ConvertSeconds();
    UseActorState();
    UsePoint2f();

}

void PrintTruthTable() 
{
    const bool falseBool{ false };
    const bool trueBool{ true };
    std::cout << "~ Print truth table ~" << std::endl;
    std::cout << "Logical binary AND-operator (&&)" << std::endl;
    std::cout << std::boolalpha << falseBool << " && " << falseBool << " is " << (falseBool && falseBool) << std::endl;
    std::cout << std::boolalpha << falseBool << " && " << trueBool << " is " << (falseBool && trueBool) << std::endl;
    std::cout << std::boolalpha << trueBool << " && " << falseBool << " is " << (trueBool && falseBool) << std::endl;
    std::cout << std::boolalpha << trueBool << " && " << trueBool << " is " << (trueBool && trueBool) << std::endl;
    std::cout << "Logical binary OR-operator (||)" << std::endl;
    std::cout << std::boolalpha << falseBool << " || " << falseBool << " is " << (falseBool || falseBool) << std::endl;
    std::cout << std::boolalpha << falseBool << " || " << trueBool << " is " << (falseBool || trueBool) << std::endl;
    std::cout << std::boolalpha << trueBool << " || " << falseBool << " is " << (trueBool || falseBool) << std::endl;
    std::cout << std::boolalpha << trueBool << " || " << trueBool << " is " << (trueBool || trueBool) << std::endl;
    std::cout << "Logical binary NOT-operator (!)" << std::endl;
    std::cout << std::boolalpha << "!" << falseBool << " is " << !falseBool << std::endl;
    std::cout << std::boolalpha << "!" << trueBool << " is " << !trueBool << std::endl;
}
void CompareTwoNumbers() 
{
    int numberOne{ rand() % 11 };
    int numberTwo{ rand() % 11 };
    std::cout << "~ Compare 2 numbers ~" << std::endl;
    std::cout << "First number is " << numberOne << std::endl;
    std::cout << "Second number is " << numberTwo << std::endl;
    if (numberOne > numberTwo) { std::cout << "First number is larger than the second one" << std::endl; }
    else { std::cout << "Second number is larger than the first one" << std::endl; }
    
}
void CalculatePrice() 
{
    unsigned int nrBallpoints{};
    const float priceLessThanTwenty{ 4.00f };
    const float priceTwentyToFifty{ 3.50f };
    const float priceFiftyToOneHundred{ 3.25f };
    const float priceOneHundredPlus{ 3.10f };
    float answer{};
    std::cout << "~ Calculate Price ~" << std::endl;
    std::cout << "NrBallpoints? "; std::cin >> nrBallpoints;

    if (nrBallpoints < 20) 
    {
        answer = nrBallpoints * priceLessThanTwenty;
    }
    else if (nrBallpoints < 50) 
    {
        answer = nrBallpoints * priceTwentyToFifty;
    }
    else if (nrBallpoints < 100) 
    {
        answer = nrBallpoints * priceFiftyToOneHundred;
    }
    else  
    {
        answer = nrBallpoints * priceOneHundredPlus;
    }
    std::cout << "Price is " << answer << std::endl;
}
void ConvertDayNumber() 
{
    unsigned int DayNumber{};
    std::cout << "Day number [1, 7]? ";
    std::cin >> DayNumber;
    if (DayNumber == 1) { std::cout << "Start of the week" << std::endl; }
    else if (DayNumber < 5) { std::cout << "Middle of the week" << std::endl; }
    else if (DayNumber == 5) { std::cout << "Nearly weekend" << std::endl; }
    else if (DayNumber < 8) { std::cout << "Weekend!" << std::endl; }
    else { std::cout << "Wrong day number" << std::endl; }
    std::cout << "Day number [1, 7]? ";
    std::cin >> DayNumber;
    switch (DayNumber)
    {
    case 1: {std::cout << "Monday" << std::endl; break; }
    case 2: {std::cout << "Tuesday" << std::endl; break; }
    case 3: {std::cout << "Wednesday" << std::endl; break; }
    case 4: {std::cout << "Thursday" << std::endl; break; }
    case 5: {std::cout << "Friday" << std::endl; break; }
    case 6: {std::cout << "Saturday" << std::endl; break; }
    case 7: {std::cout << "Sunday" << std::endl; break; }
    default: {std::cout << "Wrong day number" << std::endl; break; }
    }
}
void CheckLeapYear() 
{
    int year{};
    int daysInFebruari{};
    std::cout << "~ Check leap year ~" << std::endl;
    std::cout << "Year? ";
    std::cin >> year;
    if ((year % 4) == 0) 
    {
        if ((year % 100) == 0)
        {
            if ((year % 400) == 0) 
            {
                daysInFebruari = 29;
            }
            else { daysInFebruari = 28; }
        }
        else { daysInFebruari = 29; }
    }
    else { daysInFebruari = 28; }

    std::cout << year << " has " << daysInFebruari << " days in februari." << std::endl;
}
void ConvertSeconds() 
{
    int numberOfSeconds{};
    int days{}, minutes{}, hours{};
    std::cout << "~ Convert seconds ~" << std::endl;
    std::cout << "Number of seconds? ";
    std::cin >> numberOfSeconds;

    days = numberOfSeconds / (24 * 60 * 60);
    numberOfSeconds = numberOfSeconds % (24 * 60 * 60);
    hours = numberOfSeconds / (60 * 60);
    numberOfSeconds = numberOfSeconds % (60 * 60);
    minutes = numberOfSeconds / 60;
    numberOfSeconds = numberOfSeconds % 60;

    std::cout << days << " days " << std::endl; 
    std::cout << hours << " hours " << std::endl; 
    std::cout << minutes << " minutes " << std::endl;
    std::cout << numberOfSeconds << " seconds " << std::endl;
   

    
}
void UseActorState() 
{
    ActorState g_ActorState{ ActorState((rand() % (int(ActorState::falling) + 1) + int(ActorState::running))) };
    std::cout << "~ Define and use ActorState ~" << std::endl;
    //std::cout << (g_ActorState) << std::endl;
    switch (g_ActorState)
    {
    case ActorState::running:
        std::cout << "running\n";
        break;
    case ActorState::flying:
        std::cout << "flying\n";
        break;
    case ActorState::falling:
        std::cout << "falling\n";
        break;
    default:
        std::cout << "problem in the code!\n";
        break;
    }
}
void UsePoint2f() 
{
    struct Point2f
    {
        float x;
        float y;
    };
    Point2f testingVar1;
    Point2f testingVar2{};
    Point2f testingVar3{ 26,25 };

    std::cout << "~ Define and use Point2f ~" << std::endl;
    std::cout << "Values after definition" << std::endl;
    //std::cout << "p1: ["<< testingVar1.x << "," << testingVar1.y << "]" << std::endl;
    std::cout << "p2: ["<< testingVar2.x << "," << testingVar2.y << "]" << std::endl;
    std::cout << "p3: ["<< testingVar3.x << "," << testingVar3.y << "]" << std::endl;

    testingVar1.x = 20;
    testingVar1.y = 3;
    testingVar2 = Point2f { 30, 40 };
    testingVar3.x = ++testingVar3.x;
    testingVar3.y = --testingVar3.y;

    std::cout << "Values after changing the members" << std::endl;
    std::cout << "p1: ["<< testingVar1.x << "," << testingVar1.y << "]" << std::endl;
    std::cout << "p2: [" << testingVar2.x << "," << testingVar2.y << "]" << std::endl;
    std::cout << "p3: [" << testingVar3.x << "," << testingVar3.y << "]" << std::endl;
}
