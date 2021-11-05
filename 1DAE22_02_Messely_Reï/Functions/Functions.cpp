// Messely, Reï - 1DAE22

#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


void TestOneParFunctions();
void TestTwoParFunctions();

int main( )
{
	// 1. Show my data
	std::cout << "My name is Messely, Reï" << std::endl;
	std::cout << "I am in group 1DAE22" << std::endl << std::endl;

	// 2. Show my student history
	std::cout << "Name of my high school: Guldensporencollege Campus Engineering" << std::endl;
	std::cout << "In the last year I had 8 hours math a week" << std::endl << std::endl;

	// 3. My functions
	TestOneParFunctions();
	TestTwoParFunctions();

	// Wait
	std::cout << "Push ENTER to quit\n";
	std::cin.get( );

	return 0;
}
void TestOneParFunctions() 
{
	std::cout << cos(2) << std::endl;
	float angle{ 0 };
	std::cout << "Angle: " << angle << std::endl;
	std::cout << "Cos: " << cosf(angle) << std::endl;
	float pi{ 3.1415926535f };
	angle = angle + pi / 4;
	std::cout << "Angle: " << angle << std::endl;
	std::cout << "Cos: " << cosf(angle) << std::endl;
	angle = angle + pi / 4;
	std::cout << "Angle: " << angle << std::endl;
	std::cout << "Cos: " << cosf(angle) << std::endl;
	angle = angle + pi / 4;
	std::cout << "Angle: " << angle << std::endl;
	std::cout << "Cos: " << cosf(angle) << std::endl;
	angle = angle + pi / 4;
	std::cout << "Angle: " << angle << std::endl;
	std::cout << "Cos: " << cosf(angle) << std::endl;
	// You can also use the result of an expression as argument in a function 
	// call.Call the cosine function passing the expression angle * 2.
	std::cout << "Cos of 2* angle: " << cos(2 * angle) << std::endl;
}
void TestTwoParFunctions() 
{
	int base{ 2 };
	int exponent{ 3 };
	double result = pow(base, exponent);
	std::cout << base << " raised by the power of  " << exponent << " equals " << result << std::endl;
	int a{ 3 }, b{ 4 };
	double hypotenuse = sqrt(pow(a, 2) + pow(b, 2));
	std::cout << hypotenuse << std::endl;
}