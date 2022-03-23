#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Texture;
class Level;
class Shell;
class Mario final : public GameObject
{
public:
	explicit Mario();
	Mario(const Mario& m) = delete;
	Mario& operator=(const Mario& m) = delete;
	~Mario();

	void Draw() const;
	void Update(float elapsedSec, Level& level);
	void UpdateAnim(float elapsedSec);

	void Jump();
	void BounceJump();
	void Hurt();
	void Grow();

	void SetShell(Shell* pShell);
	Shell* GiveShell();
	Shell* GetShell() const;
	float GetHorDirection() const;

	Point2f GetPureLocation() const;
	Point2f GetMiddleBotLocation() const;

	Rectf GetRect() const;

	bool IsTryingToThrowShell() const;

private:
	// Animation stuff
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
		spinJump1 = 10,spinJump2 = 11,spinJump3 = 12,spinJump4 = 13,
		victory = 17
	};
	Texture* m_pTexture;
	bool m_IsGrabbing;
	bool m_LookUp;
	bool m_Duck;
	AnimState m_CurrentAnim;
	float m_AnimTime;
	int m_FramesPerSec;

	const float m_SpeedTreshHold;
	const float m_MaxSpeed;

	bool IsAtWalkingSpeed();
	bool IsAtRunningSpeed();

	// World loc stuff
	Point2f m_Position;
	Vector2f m_Velocity;
	float m_HorizontalDirection;
	const float m_SprintAcceleration;
	const float m_SprintDeceleration;
	const float m_WalkSpeed;
	const float m_SprintSpeed;
	float m_JumpSpeed;

	bool m_IsInAir;

	// Other stuff
	Shell* m_pShell;
	bool m_LoseShell;
};

