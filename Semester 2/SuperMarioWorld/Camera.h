#pragma once
class Camera final
{
public:
	explicit Camera(float width, float height);

	void Transform(const Rectf& target) const;
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Point2f GetPos() const;
	
	void UpdateTransitioning(const Rectf& target,float elapsedSec);

private:
	const float m_Width;
	const float m_Height;
	float m_Treshold;
	Rectf m_LevelBoundaries;
	Point2f m_PreviousPos;
	
	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};

