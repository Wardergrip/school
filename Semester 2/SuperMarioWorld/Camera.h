#pragma once
class Camera
{
public:
	Camera(float width, float height);

	void Transform(const Rectf& target) const;
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	
	void UpdateTransitioning(const Rectf& target,float elapsedSec);

private:
	const float m_Width;
	const float m_Height;
	float m_Treshold;
	Rectf m_LevelBoundaries;
	
	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

