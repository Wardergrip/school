#include "pch.h"
#include "Fraction.h"
using namespace utils;

Fraction::Fraction(int numerator, int denominator)
    :m_Numerator{numerator}
    ,m_Denominator{denominator}
{
}
Fraction::~Fraction()
{
}

void Fraction::Draw(const Point2f& pos, float size)
{
    SetColor(50 / 255.0f, 150 / 255.0f, 1, 1);
    for (int i{ 0 }; i < m_Numerator; ++i)
    {
        FillRect(pos.x + i * size, pos.y, size, size);
    }
    SetColor(1, 1, 1, 1);
    for (int i{ 0 }; i < m_Denominator; ++i)
    {
        DrawRect(pos.x + i*size, pos.y, size, size);
    }
}
float Fraction::GetValue()
{
    return (m_Numerator /  float(m_Denominator));
}
