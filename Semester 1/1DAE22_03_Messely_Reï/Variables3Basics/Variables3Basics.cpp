#include "pch.h"
#include <iostream>

int main()
{
#pragma region declaringLocalTestingVars
    const bool testingBool{};
    int testingInt{};
    const float testingFloat{};
    const double testingDouble{};
#pragma endregion
#pragma region O3.2.1
    std::cout << sizeof testingBool << std::endl;
    std::cout << sizeof testingInt << std::endl;
    std::cout << sizeof testingFloat << std::endl;
    std::cout << sizeof testingDouble<< std::endl;
#pragma endregion
#pragma region O3.2.2
    testingInt = 12;
    std::cout << testingInt << std::endl;
    testingInt = 0xC;
    std::cout << testingInt << std::endl;
    testingInt = 0b1100;
    std::cout << testingInt << std::endl;
#pragma endregion
#pragma region O3.2.3
    int signedIntOverflowMax{ INT32_MAX };
    int signedIntOverflowMin{ INT32_MIN };
    unsigned int unsignedIntOverflowMax{ UINT32_MAX };
    unsigned int unsignedIntOverflowMin{ 0 };

    std::cout << signedIntOverflowMax << " -> " << signedIntOverflowMax++ << std::endl;
    std::cout << signedIntOverflowMin << " -> " << signedIntOverflowMin-- << std::endl;
    std::cout << unsignedIntOverflowMax << " -> " << unsignedIntOverflowMax++ << std::endl;
    std::cout << unsignedIntOverflowMin << " -> " << unsignedIntOverflowMin-- << std::endl;
#pragma endregion
#pragma region O.3.2.4
    // a
    const unsigned int var1{ 3 };
    const unsigned int var2{ 5 };
    unsigned int result{ var1 & var2 };
    std::cout << result << std::endl;
    // b
    result = var1 | var2 ;
    // c
    unsigned int answer{};
    std::cout << "Number to check which bits are set? ";
    std::cin >> answer;
    std::cout << "1st bit " << (answer & 0b1) << std::endl;
    std::cout << "2nd bit " << (answer & 0b10) << std::endl;
    std::cout << "3rd bit " << (answer & 0b100) << std::endl;
    std::cout << "4th bit " << (answer & 0b1000) << std::endl;
    // d
    std::cout << "Number to set 3rd bit in? ";
    std::cin >> answer;
    std::cout << "This number with 3rd bit set " << (answer | 0b100) << std::endl;
    // f
    unsigned int excF{ 2048 };
    std::cout << (excF >> 1) << std::endl;
    // g
    unsigned int excG{ 2048 };
    std::cout << (excG << 1) << std::endl;
    // h
    unsigned int excH{ 0 };
    excH = ((1 << 22) | ( 1 << 20) | (1 << 18) | (1 << 17) | (1 << 15) | (1 << 14) | (1 << 12) | (1 << 10) | (1 << 9) | (1 << 8) | (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1)) >> 1;
    std::cout << excH << std::endl;
#pragma endregion

}