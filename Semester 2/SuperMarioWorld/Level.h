#pragma once
#include <vector>
class Level
{
public:
	Level();
	~Level();

	void DebugDraw(const Color4f& col = Color4f{1,0,0,1}) const;

	void Push_back(const Point2f& p);

	bool IsOnTop(Rectf& other) ;
	bool IsHorizontallyTouching(const Rectf& other) const;

private:
	std::vector<Point2f> m_Vertices;
};

