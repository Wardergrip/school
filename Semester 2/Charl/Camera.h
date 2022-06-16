#pragma once
class Camera final
{
public:
	Camera(float width, float height);

	void Transform(const Rectf& target) const;
	void Transform(const Point2f& target) const;
	void SetLevelBoundaries(const Rectf& levelBoundaries);

	Point2f GetCameraPosition(const Point2f& target) const;

private:
	const float m_Width;
	const float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

