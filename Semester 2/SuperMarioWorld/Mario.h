#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Level;
class Mario final : public GameObject
{
public:
	Mario();
	~Mario();

	void Draw() const;
	void Update(float elapsedSec, Level& level);

	Point2f GetPureLocation() const;
	Point2f GetMiddleBotLocation() const;

private:
	Vector2f m_Velocity;
	Vector2f m_Gravity;
	float m_LastHorDirection;
	float m_HorSpeed;
	float m_JumpSpeed;
	bool m_IsInAir;

};

