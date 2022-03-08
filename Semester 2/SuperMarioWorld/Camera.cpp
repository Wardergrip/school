#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	:m_Width{width}
	,m_Height{height}
	,m_Treshold{1.5f}
	,m_LevelBoundaries{0,0,0,0}
{
}

void Camera::Transform(const Rectf& target) const
{
	
	Point2f pos{ Track(target) };
	Clamp(pos);
	glTranslatef(-pos.x, -pos.y,0);
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::UpdateTransitioning(const Rectf& target, float elapsedSec)
{
	Point2f pos{ Track(target) };
	
	Clamp(pos);
}

Point2f Camera::Track(const Rectf& target) const
{
	Point2f outCome{ target.left + target.width / 2 - m_Width / m_Treshold, target.bottom + target.height / 2 - m_Height / 2 };
	return outCome;
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	else if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}
	else if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}
}
