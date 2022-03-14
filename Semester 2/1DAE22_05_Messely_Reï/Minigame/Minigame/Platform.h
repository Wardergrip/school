#pragma once
#include "Vector2f.h"
#include <vector>
class Texture;

class Platform
{
public:
	Platform(const Point2f& bottomLeft);
	~Platform();

	void Draw() const;

	void HandleCollision(Point2f& actorLoc, Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnground(const Point2f& actorLoc, const Rectf& actorShape, const Vector2f& velocity) const;

private:
	static Texture* m_pTexture;
	static unsigned int m_Instances;

	Rectf m_Shape;
	std::vector<Point2f> m_Vertices;
};

