#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Texture;
class PickUp : public GameObject
{
public:
	enum class PickUpType { coin, fireFlower, mushroom };
	PickUp(Texture* texture, int horAmount, float maxSec = 1.0f, int vertAmount = 1, int row = 1);
	virtual ~PickUp();

	void Draw() const;
	virtual void UpdateAnim(float elapsedSec);
	bool IsOverlapping(const Rectf& other) const;
	PickUpType GetType() const;

protected:
	PickUpType m_Type;
	Texture* m_pTexture;
	Point2f m_Position;
	int m_Frames;
	int m_ActFrame;
	float m_MaxSec;
	float m_AccuSec;

	void AdjustRectToTexture(int horAmount, float maxSec = 1.0f, int vertAmount = 1, int row = 1);
};

