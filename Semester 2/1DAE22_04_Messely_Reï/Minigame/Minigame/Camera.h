#pragma once
class Camera
{
public:
	Camera(float width, float height);

	void Transform(const Rectf& target) const;
	void SetLevelBoundaries(const Rectf& levelBoundaries);

private:
	const float m_Width;
	const float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

