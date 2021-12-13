#include "pch.h"
#include <iostream>
#include "Square.h"
#include "Time.h"

void DoSquareTests();
void TestSquare(Square* pSquare);

void DoTimeTests();

int main()
{
    DoSquareTests();
    std::cout << std::endl;
    DoTimeTests();

    std::cin.get();
}


void DoSquareTests()
{
    Square* pSq3{ new Square{10} };

    TestSquare(pSq3);
    pSq3->Print();

    delete pSq3;
    pSq3 = nullptr;
}
void TestSquare(Square* pSquare)
{
    pSquare->Translate(20, 40);
}

void DoTimeTests()
{
    Time* pTimeOne{ new Time{3661} };
    Time* pTimeTwo{ new Time{8274} };
    Time* pTimeThree{ new Time{13,56,22} };

    pTimeOne->Print();
    pTimeTwo->Print();
    pTimeThree->Print();

    delete pTimeOne;
    pTimeOne = nullptr;
    delete pTimeTwo;
    pTimeTwo = nullptr;
    delete pTimeThree;
    pTimeThree = nullptr;
}