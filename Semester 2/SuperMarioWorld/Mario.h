#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Texture;
class Level;
class Mario final : public GameObject
{
public:
	Mario();
	~Mario();

	void Draw() const;
	void Update(float elapsedSec, Level& level);
	void UpdateAnim(float elapsedSec);

	Point2f GetPureLocation() const;
	Point2f GetMiddleBotLocation() const;

	Rectf GetRect() const;

private:
	enum class AnimState 
	{
		neutral = 0,
		lookUp = 1,
		duck = 2,
		walk = 3,
		run = 4,
		runNeutral = 5,
		skid = 6,
		jump = 7,
		fall = 8,
		jumpRun = 9,
		spinJump1 = 10,spinJump2 = 11,spinJump3 = 12,spinJump4 = 13
	};
	Texture* m_pTexture;
	bool m_IsGrabbing;
	AnimState m_AnimState;

	Point2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_Gravity;
	float m_LastHorDirection;
	float m_HorSpeed;
	float m_JumpSpeed;
	bool m_IsInAir;

};

