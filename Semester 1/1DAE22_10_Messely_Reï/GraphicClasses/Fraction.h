#pragma once
#include "utils.h"

class Fraction
{
public:
	Fraction(int numerator, int denominator);
	~Fraction();

	void Draw(const Point2f& pos, float size);
	float GetValue();

private:
	int m_Numerator;
	int m_Denominator;

};