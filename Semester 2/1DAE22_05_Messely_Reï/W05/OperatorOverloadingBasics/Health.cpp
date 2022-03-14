#include "pch.h"
#include "Health.h"

Health::Health( int value) 
	: m_Value{value}
{
}
int Health::GetValue( ) const
{
	return m_Value;
}

Health& Health::operator+=(int value)
{
	m_Value += value;
	return *this;
}

Health& Health::operator-=(int value)
{
	m_Value -= value;
	return *this;
}

Health operator+(int value, const Health& health)
{
	return Health(value += health.GetValue());
}

Health operator+(const Health& health, int value)
{
	return Health(value += health.GetValue());
}

Health operator-(int value, const Health& health)
{
	return Health(value -= health.GetValue());
}

Health operator-(const Health& health, int value)
{
	int t{ health.GetValue() };
	return Health(t -= value);
}

Health& Health::operator+=(const Health& h)
{
	m_Value += h.m_Value;
	return *this;
}

Health& Health::operator-=(const Health& h)
{
	m_Value -= h.m_Value;
	return *this;
}