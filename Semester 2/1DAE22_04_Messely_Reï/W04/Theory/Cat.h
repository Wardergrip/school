#pragma once
#include "Animal.h"

class Cat : public Animal
{
public:
	Cat( );
    virtual ~Cat( );
    void MakeSound() const override;
	void SetNightVision(bool b);
private:
	bool m_NightVision;
};

 
