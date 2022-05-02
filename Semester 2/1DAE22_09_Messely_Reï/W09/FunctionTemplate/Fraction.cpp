#include "pch.h"
#include "Fraction.h"

Fraction::Fraction( ) :Fraction( 0, 1 )
{
}

Fraction::Fraction( int numerator, int denominator )
	: numerator{ numerator }
	,denominator{denominator}
{
}

bool Fraction::operator<( const Fraction& other ) const
{
	return float( numerator ) / denominator < float( other.numerator ) / other.denominator;
}

bool Fraction::operator==( const Fraction& other ) const
{
	return abs(float( numerator ) / denominator - float( other.numerator ) / other.denominator) < 0.0001f;
}

std::ostream& operator<<( std::ostream& out, const Fraction& fraction )
{
	out << fraction.numerator << "/" << fraction.denominator;
	return out;
}

