#include "pch.h"
#include "Float2.h"


Float2::Float2(float x,float y)
	:m_X{x}
	,m_Y{y}
{
}

Float2& Float2::operator+=(const Float2& r)
{
	m_X += r.m_X;
	m_Y += r.m_Y;
	return *this;
}

Float2 operator+(const Float2& l, const Float2& r)
{
	Float2 t{l};
	t += r;
	return t;
	
	// Friend
	//return Float2{ l.m_X + r.m_X,l.m_Y + r.m_Y };
}

std::ostream& operator<<(std::ostream& out, const Float2& rhs)
{
	out << "( " << rhs.m_X << ", " << rhs.m_Y << " )";
	return out;
}