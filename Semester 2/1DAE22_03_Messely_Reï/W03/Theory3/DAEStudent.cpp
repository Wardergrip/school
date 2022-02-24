#include "pch.h"
#include "DAEStudent.h"
#include <iostream>

DAEStudent::DAEStudent(const std::string& firstName, const std::string& lastName, Major major)
	:Person{firstName,lastName}
	,m_Major{major}
{
	std::cout << "DAEStudent constructor\n";
}

DAEStudent::~DAEStudent()
{
	std::cout << "DAEStudent destructor\n";
}

void DAEStudent::Identify() const
{
	//Person::Identify();
	std::cout << "My name is " << GetName();
}

std::string DAEStudent::GetName() const
{
	std::string name{Person::GetName()};
	name += ". My major is ";
	switch (m_Major)
	{
	case DAEStudent::Major::GD:
		name += "GD.";
		break;
	case DAEStudent::Major::SD:
		name += "SD.";
		break;
	case DAEStudent::Major::GGP:
		name += "GGP.";
		break;
	case DAEStudent::Major::IGP:
		name += "IGP.";
		break;
	case DAEStudent::Major::VFX:
		name += "VFX.";
		break;
	case DAEStudent::Major::ANI:
		name += "ANI.";
		break;
	}
	name += '\n';
	return name;
}
