#pragma once
#include "PickUp.h"
class Level;
class Mushroom final : public PickUp
{
public:
	explicit Mushroom(Type type, Level* levelReference, const Point2f& pos = {});
	Mushroom(const Mushroom& m) = delete;
	Mushroom& operator=(const Mushroom& m) = delete;
	Mushroom(Mushroom&& m) = delete;
	Mushroom& operator=(Mushroom&& m) = delete;
	~Mushroom() = default;

	void Update(float elapsedSec);

private:
	Vector2f m_Velocity;
	Level* m_LevelRef;
};

