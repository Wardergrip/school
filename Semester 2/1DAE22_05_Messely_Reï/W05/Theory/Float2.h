#pragma once
#include <iostream>
class Float2 final
{
public:
	Float2(float x = 0, float y = 0);
	
	//friend Float2 operator+(const Float2 & l, const Float2 & r);
	Float2& operator+=(const Float2& r);
	friend std::ostream& operator<<(std::ostream& out, const Float2& rhs);

private:
	float m_X;
	float m_Y;
};

Float2 operator+(const Float2& l, const Float2& r);