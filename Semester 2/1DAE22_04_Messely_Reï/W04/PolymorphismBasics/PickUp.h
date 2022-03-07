#pragma once
#include "GameObject.h"

class PickUp : public GameObject
{
public:
	PickUp( );
	~PickUp( );

	std::string ToString() const override;

private:
	static int m_InstanceCounter;
};
