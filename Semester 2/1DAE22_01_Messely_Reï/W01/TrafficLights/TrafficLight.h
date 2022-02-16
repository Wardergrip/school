#pragma once
#include <vector>

class TrafficLight
{
public:
	enum class State 
	{
		green,
		orange,
		red,
		off
	};

	TrafficLight(const Point2f& pos);
	~TrafficLight();

	void DoHitTest(const Point2f& point);
	void Draw() const;
	void Update(float elapsedSec);

	float GetWidth();
	float GetHeight();

private:
	State m_State;
	Point2f m_Position;
	float m_AccumulatedSec;
	Rectf m_Rect;
	std::vector<Circlef*> m_pLights;

};

