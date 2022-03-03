#include "pch.h"		
#include "Dog.h"

Dog::Dog():m_SurveillanceMode{false}
	, Animal(AnimalType::dog)
{
	std::cout << "Dog constructor\n";
}

Dog::~Dog()
{
	std::cout << "Dog destructor.\n";
}

void Dog::MakeSound()const
{
	if(m_SurveillanceMode) std::cout <<"I am in surveillance mode: Wafwaf\n";
	else std::cout << "I am a sleeping dog. Watch out.\n";
}

void Dog::SetSurveillanceMode(bool value)
{
	std::cout << "Setting surveillance mode.\n";
	m_SurveillanceMode = value;
}




