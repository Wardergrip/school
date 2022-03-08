#pragma once
#include <vector>
#include "utils.h"
class PickUp;
class Platform;
class Player;
class Level final
{
public:
	Level(Player& player);
	~Level();

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void DrawPickUps() const;
	void UpdatePickUps(float elapsedSec, const Rectf& other);

	void Push_back(const Point2f& p);
	void Push_back(PickUp* pu);
	void Push_back(Platform* p);

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity);
	bool IsHorizontallyTouching(const Rectf& other) const;

private:
	bool m_EnableDebugDraw;
	Player& m_Player;

	std::vector<std::vector<Point2f>> m_Vertices;
	std::vector<PickUp*> m_pPickUps;
	std::vector<Platform*> m_pPlatforms;

	void PushDemoLevel();
	void PushDemoPickUps();
};

