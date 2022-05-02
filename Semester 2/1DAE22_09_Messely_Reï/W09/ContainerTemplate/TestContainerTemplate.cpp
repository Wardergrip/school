#include "pch.h"
#include "TestContainerTemplate.h"
#include "Fraction.h"
#include <string>

template<>
int GetRandomElement( )
{
	return rand( );
}

template<>
float GetRandomElement( )
{
	return float( rand( ) ) / 100.0f;
}

template<>
Fraction GetRandomElement( )
{
	int den{ rand( ) % 5 + 2 };
	int num{ rand( ) % den + 1 };
	return Fraction{ num, den };
}

template<>
std::string GetRandomElement( )
{
	std::string random;
	for ( int nr = 1; nr < 5; ++nr )
	{
		random += std::to_string( char( rand( ) % ( 'z' - 'a' + 1 ) + 'a' ) );
	}
	return random;
}

