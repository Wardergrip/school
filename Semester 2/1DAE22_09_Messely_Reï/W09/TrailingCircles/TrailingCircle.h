#pragma once
#include "Vector2f.h"
#include <deque>

class TrailingCircle
{
public:
	TrailingCircle( float radius, const Point2f& center);
	void Update( float elapsedSec, const Rectf& boundingRect );
	void Draw( ) const;

private:
	const float m_Radius;
	const Color4f m_Color;
	Point2f m_Center;
	Vector2f m_Velocity;

	std::deque<Point2f> m_TrailPoints;
	float m_DequeTimer;
	float m_TimerTreshold;
	size_t m_DequeMaxSize;

	Vector2f GetRandomVelocity( );
	Color4f GetRandomColor( );
};
