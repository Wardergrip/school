#include "pch.h"
#include "Square.h"
#include <iostream>

Square::Square(float size, float left, float bottom)
	:m_Left{ left }
	,m_Bottom{bottom}
	,m_Size{size}
{
}
Square::Square(float size) :Square(size, 0, 0)
{
}
Square::~Square()
{
	std::cout << "Square destructor: release the resources\n";
}
// -------------------------------------------------------------------------------

void Square::Print()
{
	std::cout << "Left: " << m_Left << ", bottom: " << m_Bottom << std::endl;
	std::cout << "Size: " << m_Size << std::endl;
	std::cout << "Perimeter: " << GetPerimeter() << std::endl;
	std::cout << "Area: " << GetArea() << std::endl;
}

void Square::Translate(float deltaleft, float deltaBottom)
{
	m_Left += deltaleft;
	m_Bottom += deltaBottom;
}

void Square::SetSize(float newSize)
{
	if (newSize > 0)
	{
		m_Size = newSize;
	}
}

float Square::GetArea()
{
	return (m_Size * m_Size);
}

float Square::GetPerimeter()
{
	return (4*m_Size);
}
