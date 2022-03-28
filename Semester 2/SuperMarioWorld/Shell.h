#pragma once
#include "KoopaBase.h"
class Shell final : public KoopaBase
{
public:
	explicit Shell(Color col = Color::green);

	void Kick(float horizontalDirection);
	void Throw(float horizontalDirection, const Vector2f& velocity);

	void Draw() const override;
	void Update(float elapsedSec, const Player& player) override;

	bool IsGrabbed() const;
	float GetYPos() const;

	void SetDeathStatus(bool status);

private:
	static int m_FramesPerSec;
	static float m_KickSpeed;

	float m_AnimTime;
	int m_CurrentFrame;

	bool m_Grab;
	bool m_IsDead;
};

