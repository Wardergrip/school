#pragma once
class DaeEllipse
{
public:
	DaeEllipse(const Point2f& center, float radX, float radY, const Color4f& fillColor);
	void Draw();
	void ActivateTest(const Point2f& pos);

private:
	Point2f m_Center;
	float m_RadX;
	float m_RadY;
	Color4f m_FillColor;
	float m_Area;
	bool m_IsActive;
	
};

