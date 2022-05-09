#pragma once
#include "GameObject.h"
class Texture;
class Mario;
class Player;
class CheckPoint : public GameObject
{
public:
	explicit CheckPoint(const Point2f& pos);
	CheckPoint(CheckPoint& c) = delete;
	CheckPoint& operator=(CheckPoint& c) = delete;
	CheckPoint(CheckPoint&& c) = delete;
	CheckPoint& operator=(CheckPoint&& c) = delete;
	virtual ~CheckPoint();

	void Draw() const;
	void Update(float elapsedSec, Player* player);

	Rectf GetRect() const;
	Point2f GetPosition() const;

protected:
	static Texture* m_pTexture;
	static int m_Instances;
	bool m_IsTriggered;
	Point2f m_Position;

	Rectf m_BarRect;
	Point2f m_BarPos;
	float m_VerticalVelocity;

	virtual void TriggerLogic(Player* player);
};

