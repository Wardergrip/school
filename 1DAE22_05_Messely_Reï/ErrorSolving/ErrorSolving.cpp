// Messely, Reï
// 1DAE22

// Include directives
#include "pch.h"
#include <iostream>
#include <ctime>
#include <string> 

#pragma region Function declarations
// Function declarations
void ShowMultiplyTable( );
void GuessNumber( );
void DetermineSkill( );
void GetNumber( );
void GetColorCodes( );

void Wait( );
#pragma endregion Function declarations

int main( )
{
	std::cout << "== ErrorSolving - Messely, Reï - 1DAE22 ==\n";
	// rand seed
	srand( unsigned int( time( nullptr ) ) );

	ShowMultiplyTable( );
	GuessNumber( );
	DetermineSkill( );
	GetNumber( );
	GetColorCodes( );

	Wait( );
}

#pragma region Function definitions
// Function definitions
void GetColorCodes( )
{
	enum class ColorMenuChoice
	{
		stop, magenta, yellow, cyan
	};
	ColorMenuChoice ChoiceOfColor{};
	std::cout << "\n-- GetColorCodes function --\n";

	std::string menu{ "\nMake your choice\n" +
		std::to_string(int(ColorMenuChoice::stop)) + ".Stop\n" +
		std::to_string(int(ColorMenuChoice::magenta)) + ".Magenta\n" +
		std::to_string(int(ColorMenuChoice::yellow)) + ".Yellow\n" +
		std::to_string(int(ColorMenuChoice::cyan)) + ".Cyan\n?" };
	bool quit{ false };
	int choice{};
	do
	{
		std::cout << menu;
		std::cin >> choice;
		ChoiceOfColor = ColorMenuChoice(choice);
		switch ( ChoiceOfColor )
		{
		case ColorMenuChoice::stop:
			quit = true;
			break;
		case ColorMenuChoice::magenta:
			std::cout << "Magenta 0xFF00FF\n";
			break;
		case ColorMenuChoice::yellow:
			std::cout << "Yellow 0xFFFF00\n";
			break;
		case ColorMenuChoice::cyan:
			std::cout << "Cyan 0x00FFFF\n";
			break;
		default:
			std::cout << "Wrong choice\n";
			break;
		}
	}
	while ( quit == false );
	std::cin.ignore( );
}

void ShowMultiplyTable( )
{
	std::cout << "\n-- ShowMultiplyTable function --\n";

	int table{ 5 };
	int times{ 0 };
	std::cout << "Multiply " << table << " table\n";
	for ( times = 0; times <= 10; ++times )
	{
		std::cout << table << " x " << times << " = " << table * times << std::endl;
	}
}

void GuessNumber( )
{
	std::cout << "\n-- GuessNumber function --\n";

	int randNr{ rand( ) % 10 + 1 };
	int guess{};
	int trials{ 0 };
	do
	{
		std::cout << "Number in [0, 10] ? ";
		std::cin >> guess;
		trials++;
	}
	while ( guess != randNr );

	std::cout << "You entered the right number "<< randNr << " after " << trials << " guesses!\n";
	std::cin.ignore( );
}

void DetermineSkill( )
{
	std::cout << "\n-- DetermineSkill function --\n";

	int years{};
	std::cout << "Your years of experience ? ";
	std::cin >> years;
	std::string level{};
	if ( years < 5 )
	{
		level = "Junior level";
	}
	else if ( years < 10 )
	{
		level = "Intermediate level";
	}
	else
	{
		level = "Senior level";
	}
	std::cout << level << std::endl;

	std::cin.ignore( );
}

void GetNumber( )
{
	std::cout << "\n-- GetNumber function --\n";

	const int min{ 5 };
	const int max{ 10 };
	int nr{};
	std::string questionMsg{ "Enter a number in the interval [" + std::to_string( min ) + ", " + std::to_string( max ) + "] " };
	std::string errorMsg{ "Sorry, but this is not a correct number\n" };
	bool wrongInput{ false };
	do
	{
		if ( wrongInput == true )
		{
			std::cout << errorMsg;
		}
		std::cout << questionMsg;
		std::cin >> nr;

		wrongInput = true;
	}
	while ( nr < min || nr > max );
	std::cout << "You entered the number " << nr << '\n';

	std::cin.ignore( );
}

void Wait( )
{
	std::cout << "Press ENTER to quit";
	std::cin.get( );
}
#pragma endregion Function definitions
