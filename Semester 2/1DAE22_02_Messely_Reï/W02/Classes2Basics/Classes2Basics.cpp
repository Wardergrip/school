// Classes2Basics - 1DAE22 Reï Messely
#include "pch.h"
#include <iostream>
#include "Square.h"
#include "Time.h"
#include <vector>

void TestSquares();
void CompareTimes(const Time* t1, const Time* t2);
void PrintInstancesCntr(const std::string& msg);

int main()
{
    //std::cout << "Hello World!\n";
    TestSquares();
#pragma region TestingCompareTimes
    Time* pTime1{new Time(51503)}, * pTime2{new Time(450)};

    CompareTimes(pTime1, pTime1);
    CompareTimes(pTime1, pTime2);

    delete pTime1;
    pTime1 = nullptr;
    delete pTime2;
    pTime2 = nullptr;
#pragma endregion
#pragma region TestTimeArray
    Time* timePtrs[4];
    PrintInstancesCntr("Before");
    for (int i{ 0 }; i < 4; ++i)
    {
        timePtrs[i] = nullptr;
    }
    PrintInstancesCntr("After making a few nullptrs");
    for (int i{0}; i < 4; ++i)
    {
        timePtrs[i] = new Time(rand() % 10001);
    }
    PrintInstancesCntr("After making objs");
    for (int i{ 0 }; i < 4; ++i)
    {
        delete timePtrs[i];
    }
    PrintInstancesCntr("Deletus");

#pragma endregion


}


void TestSquares() 
{
    Square* pSquare1{ new Square(10) };
    Square* pSquare2{ new Square(10,20,30) };

    pSquare1->Print();
    std::cout << '\n';
    pSquare2->Print();

    delete pSquare1;
    pSquare1 = nullptr;
    delete pSquare2;
    pSquare2 = nullptr;
}
void CompareTimes(const Time* t1, const Time* t2)
{
    std::cout << "Comparing 2 time objects:\n";
    t1->Print();
    t2->Print();
    if ((t1->GetHours() == t2->GetHours()) && (t1->GetMinutes() == t2->GetMinutes()) && (t1->GetSeconds() == t2->GetSeconds()))
    {
        std::cout << "They are equal\n";
    }
    else 
    {
        std::cout << "They are not equal\n";
    }
}
void PrintInstancesCntr(const std::string& msg)
{
    std::cout << msg << "-> Nr of Time Instances: " << (Time::GetNrInstances()) << '\n';
}