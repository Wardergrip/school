#pragma once
#include "KoopaBase.h"
class Shell final : public KoopaBase
{
public:
	Shell(Color col = Color::green);

	void Kick(float horizontalDirection);

	void Update(float elapsedSec, Mario* pMario);

private:
	static int m_FramesPerSec;
	static float m_KickSpeed;

	float m_AnimTime;
	int m_CurrentFrame;
};

