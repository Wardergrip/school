#pragma once
class Vehicle
{
public:
	Vehicle(int id);
	~Vehicle();
	void Update(float elapsedSec, float windowWidth);
	void Draw();
	bool IsIntersecting(const Point2f& pt);
	void SetYPos(float posY);
	void Reset();
 	void SetActive(bool isActive);

private:

	const int m_MaxSpeed, m_MinSpeed;
	float m_Speed;
	Point2f m_Position;
	bool m_IsActive;
	utils::Texture m_Texture;
};


