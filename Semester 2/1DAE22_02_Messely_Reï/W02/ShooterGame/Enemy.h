#pragma once
class Enemy
{
public:
	Enemy(const Point2f& center, float width, float height);
	Enemy();
	void Draw() const;
	bool DoHitTest(const Rectf& other);

	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);

	bool IsDead();

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	bool m_IsDead;

};

