#pragma once
#include <vector>
#include "utils.h"
class Texture;
class PickUp;
class Platform;
class Player;
class Mario;
class Level final
{
public:
	Level(Player& player);
	~Level();

	void Draw(const Point2f& cameraLoc, bool debugDraw = false) const;
	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void DrawPickUps() const;
	void UpdatePickUps(float elapsedSec, Mario* mario);

	void Push_back(const Point2f& p);
	void Push_back(PickUp* pu);
	void Push_back(Platform* p);

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity);
	bool IsHorizontallyTouching(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity) const;

private:
	bool m_EnableDebugDraw;
	Player& m_Player;

	std::vector<std::vector<Point2f>> m_Vertices;
	std::vector<PickUp*> m_pPickUps;
	std::vector<Platform*> m_pPlatforms;

	Texture* m_pBackgroundTexture;

	void PushDemoLevel();
	void PushDemoPickUps();
};

