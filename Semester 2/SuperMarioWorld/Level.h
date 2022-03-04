#pragma once
#include <vector>
#include "utils.h"

class Level final
{
public:
	Level();
	~Level();

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void Push_back(const Point2f& p);

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi);
	bool IsHorizontallyTouching(const Rectf& other) const;

private:
	std::vector<Point2f> m_Vertices;
};

