#pragma once
#include <vector>
#include "utils.h"
class Platform final
{
public:
	explicit Platform(const Rectf& rect);
	explicit Platform(const Point2f& start, float length, float downwardsThickness = 2.0f);
	Platform(const Platform& p) = delete;
	Platform& operator=(const Platform& p) = delete;
	Platform(Platform&& p) = delete;
	Platform& operator=(Platform&& p) = delete;
	~Platform() = default;

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}, float lineThickness = 1) const;

	void GetVertices(std::vector<Point2f>& output) const;
	std::vector<Point2f> GetVertices() const;

	bool IsOnTop(Rectf& other);
	bool IsOnTop(const Rectf& other, utils::HitInfo& hi);
	bool IsFullyOnTop(const Rectf& other);
	bool IsHorizontallyTouching(const Rectf& other, utils::HitInfo& hi, const Vector2f& velocity, float horDirection) const;
private:
	std::vector<Point2f> m_Vertices;
};

