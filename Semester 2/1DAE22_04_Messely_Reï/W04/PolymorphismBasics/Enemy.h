#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy( );
	~Enemy( );

	std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};


 
