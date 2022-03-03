#include "pch.h"

#include "Cat.h"
#include "Dog.h"
#include <vector>

int main()
{
	std::cout << "\n\n\nVector of base class pointers\n";
	std::vector<Animal*>animals;
	animals.push_back(new Dog{});
	animals.push_back(new Cat{});
	animals.push_back(new Cat{});
	animals.push_back(new Dog{});
	animals.push_back(new Dog{});
	animals.push_back(new Cat{});
	for (Animal*pAnimal : animals)
	{
		pAnimal->MakeSound();
	}

	// Zet van alle katten de nightvision aan en alle honden surveillancemode aan
	/*for (Animal* pAnimal : animals)
	{
		Cat* pCat{ dynamic_cast<Cat*>(pAnimal) };
		if (pCat != nullptr)
		{
			pCat->SetNightVision(true);
		}
		if (typeid(*pAnimal) == typeid(Dog))
		{
			Dog* pDog{ static_cast<Dog*>(pAnimal) };
			pDog->SetSurveillanceMode(true);
		}
	}*/
	// Same as above but more performace but less flexibility
	for (Animal* pAnimal : animals)
	{
		if (pAnimal->GetAnimalType() == Animal::AnimalType::cat)
		{
			Cat* pCat{ static_cast<Cat*>(pAnimal) };
			pCat->SetNightVision(true);
		}
		else if (pAnimal->GetAnimalType() == Animal::AnimalType::dog)
		{
			Dog* pDog{ static_cast<Dog*>(pAnimal) };
			pDog->SetSurveillanceMode(true);
		}
	}

	for (Animal* pAnimal : animals)
	{
		pAnimal->MakeSound();
	}

	for (Animal*pAnimal : animals)
	{
		delete pAnimal;
	}


	return 0;
}

