#pragma once
#include "Vector2f.h"
class Level;
class Avatar
{
public:
	enum class ActionState
	{
		waiting, moving, transforming
	};
	Avatar();

	void Draw() const;
	void Update(float elapsedSec, const Level& level);
	void PowerUpHit();
	Rectf GetShape() const;

private:
	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	int m_Power;
};

