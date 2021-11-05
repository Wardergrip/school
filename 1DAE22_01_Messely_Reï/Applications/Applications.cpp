// Messely Reï - 1DAE22
#include "pch.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

int main()
{
#pragma region RGBA Application
	int red{};
	int green{};
	int blue{};
	int alpha{};

	std::cout << "RGBA in [0, 255]? ";
	std::cin >> red >> green >> blue >> alpha;
	std::cout << "RGBA in [0.0f, 1.0f]:" << std::endl;
	std::cout << "R: " << float(red / 255.0) << std::endl;
	std::cout << "G: " << float(green / 255.0) << std::endl;
	std::cout << "B: " << float(blue / 255.0) << std::endl;
	std::cout << "A: " << float(alpha / 255.0) << std::endl;

#pragma endregion
#pragma region km to m & cm converter
	float answer{};
	std::cout << "Distance in km? ";
	std::cin >> answer;
	std::cout << answer * 1000 << " meters. " << answer * 1000 * 1000 << " centimeters." << std::endl;
#pragma endregion
#pragma region Angle in radians
	answer = 0;
	std::cout << "Angle in radians? ";
	std::cin >> answer;
	std::cout << (answer / (2 * M_PI)) * 360.0f << " degrees" << std::endl;
#pragma endregion
#pragma region Angle in degrees
	answer = 0;
	std::cout << "Angle in degrees? ";
	std::cin >> answer;
	std::cout << (double(answer) / 360.0f) * 2 * M_PI << " degrees" << std::endl;
#pragma endregion
#pragma region Degree per second
	answer = 0;
	std::cout << "Seconds of one rotation? ";
	std::cin >> answer;
	std::cout << 360.0f / answer << " degrees/second" << std::endl;
#pragma endregion
#pragma region Traveled distance
	int speed{};
	int time{};
	std::cout << "Speed? (km/h)";
	std::cin >> speed;
	std::cout << "Elapsed time (minutes)? ";
	std::cin >> time;
	std::cout << (speed * (time/60.0f)) * 1000 << " meters traveled." << std::endl;
#pragma endregion
#pragma region Velocity when falling
	answer = 0;
	std::cout << "How long are you falling? ";
	std::cin >> answer;
	std::cout << answer * 9.8f << " m/s" << std::endl;
#pragma endregion
#pragma region Radius of circle
	answer = 0;
	std::cout << "Radius of circle? ";
	std::cin >> answer;
	std::cout << "Circumference: " << 2 * double(answer) * M_PI << std::endl;
	std::cout << "Area: " << double(answer) * answer * M_PI << std::endl;
#pragma endregion
#pragma region Area of triangle
	float base{};
	float height{};
	std::cout << "Base & height of triangle? ";
	std::cin >> base >> height;
	std::cout << "Area: " << (base*height)/2 << std::endl;
#pragma endregion
}