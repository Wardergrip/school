#pragma once
#include <vector>
#include "utils.h"
class Platform final
{
public:
	explicit Platform(const Rectf& rect);
	explicit Platform(const Point2f& start, float length, float downwardsThickness = 2.0f);

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}, float lineThickness = 1) const;

	void GetVertices(std::vector<Point2f>& output) const;
	std::vector<Point2f> GetVertices() const;

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi);
	bool IsFullyOnTop(const Rectf& other);
private:
	std::vector<Point2f> m_Vertices;
};

