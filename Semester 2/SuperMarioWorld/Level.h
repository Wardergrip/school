#pragma once
#include <vector>
#include "utils.h"
class PickUp;
class Level final
{
public:
	Level();
	~Level();

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void DrawPickUps() const;
	void UpdatePickUps(float elapsedSec, const Rectf& other);

	void Push_back(const Point2f& p);
	void Push_back(PickUp* pu);

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi);
	bool IsHorizontallyTouching(const Rectf& other) const;

private:
	std::vector<Point2f> m_Vertices;
	std::vector<PickUp*> m_PickUps;

	void PushDemoLevel();
	void PushDemoPickUps();
};

