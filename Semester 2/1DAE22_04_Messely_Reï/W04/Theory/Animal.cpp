#include "pch.h"			
#include "Animal.h"

Animal::Animal(AnimalType type)
	:m_Type{type}
{
	std::cout << "Animal constructor\n";
}

Animal::~Animal()
{
	std::cout << "Animal destructor\n";
}

void Animal::MakeSound() const
{
	std::cout <<"I am an Animal, I have no idea what sound to make!\n";
}

Animal::AnimalType Animal::GetAnimalType()
{
	return m_Type;
}

