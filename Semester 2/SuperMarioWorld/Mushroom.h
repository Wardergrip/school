#pragma once
#include "PickUp.h"
class Level;
class Mushroom final : public PickUp
{
public:
	Mushroom(Level* levelReference, const Point2f& pos = {});

	void Update(float elapsedSec);

private:
	Vector2f m_Velocity;
	Level* m_LevelRef;
};

