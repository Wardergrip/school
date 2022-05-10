#pragma once
#include "GameObject.h"
class Texture;
class PickUp : public GameObject
{
public:
	enum class Type { coin = -1, bigCoin = 0, normalMushroom = 1, fireFlower = 2, oneUpMushroom = 3 };
	
	explicit PickUp(Type type, Texture* texture, int horAmount, float maxSec = 1.0f, int vertAmount = 1, int row = 1);
	PickUp(const PickUp& p) = delete;
	PickUp& operator=(const PickUp& p) = delete;
	PickUp(PickUp&& p) = delete;
	PickUp& operator=(PickUp&& p) = delete;
	virtual ~PickUp();

	void Draw() const;
	virtual void Update(float elapsedSec);
	virtual void UpdateAnim(float elapsedSec);

	bool IsOverlapping(const Rectf& other) const;
	Type GetType() const;

	void SetPosition(const Point2f& pos);

protected:
	const Type m_Type;
	Texture* m_pTexture;
	Point2f m_Position;
	int m_Frames;
	int m_ActFrame;
	float m_MaxSec;
	float m_AccuSec;

	void AdjustRectToTexture(int horAmount, float maxSec = 1.0f, int vertAmount = 1, int row = 1);
};

