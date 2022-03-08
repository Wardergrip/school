#pragma once
#include "Vector2f.h"
class Level;
class Texture;
class Avatar
{
public:
	enum class ActionState
	{
		waiting = 0, moving = 1, transforming = 2
	};
	Avatar();
	~Avatar();

	void Draw() const;
	void Update(float elapsedSec, const Level& level);
	void PowerUpHit();
	Rectf GetShape() const;

private:
	const Texture* m_pSpritesTexture;
	const float m_ClipHeight;
	const float m_ClipWidth;
	const int m_NrOfFrames;
	const int m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	Point2f m_Position;
	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	ActionState m_ActionState;
	float m_AccuTransformSec;
	float m_MaxTransformSec;
	int m_Power;

	void UpdateAnim(float elapsedSec);
};

