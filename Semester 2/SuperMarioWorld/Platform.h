#pragma once
#include <vector>
#include "utils.h"
class Platform final
{
public:
	Platform(const Rectf& rect);
	Platform(const Point2f& start, float length, float downwardsThickness = 2.0f);
	~Platform();

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void GetVertices(std::vector<Point2f>& output) const;
	std::vector<Point2f> GetVertices() const;

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi);
private:
	std::vector<Point2f> m_Vertices;
};

