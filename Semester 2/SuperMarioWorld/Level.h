#pragma once
#include <vector>
#include "utils.h"
class Texture;
class PickUp;
class Platform;
class Player;
class Mario;
class Shell;
class Koopa;
class MysteryBox;
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
	void Push_back(PickUp* pu);
	void Push_back(Platform* p);
	void Push_back(Shell* s);

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity);
	bool IsFullyOnTop(const Rectf& other, const Vector2f& velocity);
	bool IsHorizontallyTouching(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity, float horDirection) const;

	bool SwitchDebugDrawLevel();

	float GetFurthestXValue() const;

private:
	bool m_EnableDebugDraw;
	Player& m_Player;

	std::vector<std::vector<Point2f>> m_Vertices;
	std::vector<PickUp*> m_pPickUps;
	std::vector<Platform*> m_pPlatforms;
	std::vector<MysteryBox*> m_pMysteryBoxes;
	std::vector<CheckPoint*> m_pCheckPoints;

	Texture* m_pBackgroundTexture;
	Texture* m_pLevelTexture;

	std::vector<Shell*> m_pShells;
	std::vector<Koopa*> m_pKoopas;

	// Scale the level. vectorAmount indicates until what idx the vectors should be scaled.
	// -1 will scale all vectors.
	void ScaleLevel(float scale, int vectorAmount = -1);

	void PushPlatforms();
	void PushPickups();

	void PushDemoLevel();
	void PushDemoPickUps();

	void DrawPickUps() const;
};

