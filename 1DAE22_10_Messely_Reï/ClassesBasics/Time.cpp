#include "pch.h"
#include "Time.h"
#include <iostream>

Time::Time(unsigned int seconds) :Time(seconds, 0, 0)
{
}
Time::Time(unsigned int seconds, unsigned int minutes):Time(seconds,minutes,0)
{
}
Time::Time(unsigned int seconds, unsigned int minutes, unsigned int hours)
	:m_Seconds{seconds + minutes * 60 + hours * 3600}
{
}
Time::~Time()
{
}

void Time::Print()
{
	const unsigned int hours{m_Seconds / 3600};
	const unsigned int minutes{(m_Seconds % 3600) / 60};
	const unsigned int seconds{ (m_Seconds % 3600) % 60 };
	std::cout << "Time: " << hours << ':' << minutes << ':' << seconds << '\n';
}


unsigned int Time::GetSeconds()
{
	return ((m_Seconds % 3600) % 60);
}
unsigned int Time::GetMinutes()
{
	return ((m_Seconds % 3600) / 60);
}
unsigned int Time::GetHours()
{
	return (m_Seconds / 3600);
}

void Time::AddSeconds(int seconds)
{
	m_Seconds += seconds;
}

void Time::AddMinutes(int minutes)
{
	m_Seconds += (minutes * 60);
}

void Time::AddHours(int hours)
{
	m_Seconds += (hours * 3600);
}


