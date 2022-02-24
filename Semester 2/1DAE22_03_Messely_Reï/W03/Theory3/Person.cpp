#include "pch.h"
#include "Person.h"
#include <iostream>

Person::Person(const std::string& firstName, const std::string& lastName)
	: m_FirstName{firstName}
	, m_LastName{lastName}
{
	std::cout << "Base constructor.\n";
}

Person::~Person()
{
	std::cout << "Base destructor.\n";
}

std::string Person::GetName() const
{ 
	return m_FirstName + " " + m_LastName;
}

void Person::Identify()const
{
	std::cout << "I am a base class Person object. My name is: " << GetName() << "\n";
}