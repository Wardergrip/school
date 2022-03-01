#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Texture;
class PowerUp : public GameObject
{
public:
	PowerUp(Texture* texture, int frameAmount, float maxSec = 1.0f);
	~PowerUp();

	void Draw() const;
	void Update(float elapsedSec);

protected:
	Texture* m_pTexture;
	Vector2f m_Velocity;
	Point2f m_Position;
	int m_Frames;
	int m_ActFrame;
	float m_MaxSec;
	float m_AccuSec;

	bool IsOverlapping(const Rectf& other) const;
};

