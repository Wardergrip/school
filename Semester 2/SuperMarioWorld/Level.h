#pragma once
#include <vector>
#include "utils.h"
class Texture;
class PickUpManager;

class KoopaBaseManager;
class Shell;

class MysteryBoxManager;
class MysteryBox;

class Platform;
class Player;
class Mario;
class CheckPoint;
class Level final
{
public:
	explicit Level(Player& player);
	Level(const Level& l) = delete;
	Level& operator=(const Level& l) = delete;
	Level(Level&& l) = delete;
	Level& operator=(Level&& l) = delete;
	~Level();

	void Draw(const Point2f& cameraLoc, bool debugDraw = false) const;
	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}, float lineThickness = 1) const;


	void UpdateContent(float elapsedSec, Mario* mario);

	void Push_back(const Point2f& p);
	void Push_back(Platform* p);
	void Push_back(MysteryBox* m);

	void Push_back(Shell* shell, const Point2f& point = {});

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity);
	bool IsFullyOnTop(const Rectf& other, const Vector2f& velocity);
	bool IsHorizontallyTouching(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity, float horDirection) const;

	bool SwitchDebugDrawLevel();

	float GetFurthestXValue() const;

private:
	bool m_EnableDebugDraw;
	Player& m_Player;

	PickUpManager* m_pPickUpManager;
	KoopaBaseManager* m_pKoopaBaseManager;
	MysteryBoxManager* m_pMysteryBoxManager;
	std::vector<std::vector<Point2f>> m_Vertices;
	std::vector<Platform*> m_pPlatforms;
	std::vector<CheckPoint*> m_pCheckPoints;

	Texture* m_pBackgroundTexture;
	Texture* m_pLevelTexture;

	// Scale the level. vectorAmount indicates until what idx the vectors should be scaled.
	// -1 will scale all vectors.
	void ScaleLevel(float scale, int vectorAmount = -1);

	void PushPlatforms();

	void PushDemoLevel();
	void PushDemoPickUps();
};

