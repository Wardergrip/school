#pragma once
#include <iostream>

struct Fraction final
{
	Fraction(  );
	Fraction( int numerator, int denominator );

	bool operator<( const Fraction& other ) const;
	bool operator==( const Fraction& other ) const;

	int numerator;
	int denominator;
};

std::ostream& operator<<( std::ostream& out, const Fraction& fraction );
