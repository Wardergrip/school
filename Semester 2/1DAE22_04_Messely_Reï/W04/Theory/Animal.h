#pragma once
class Animal
{
public:
	enum class AnimalType { animal, cat, dog };

	Animal(AnimalType type);
	virtual ~Animal(); // Makes sure derrived classes' destructor is called
	virtual void MakeSound()const; 
	AnimalType GetAnimalType();
protected:
	AnimalType m_Type;
};

 
