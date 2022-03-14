#include "pch.h"
#include "Platform.h"
#include "Texture.h"

#include "utils.h"
using namespace utils;

Texture* Platform::m_pTexture{ nullptr };
unsigned int Platform::m_Instances{ 0 };

Platform::Platform(const Point2f& bottomLeft)
	:m_Shape{bottomLeft.x,bottomLeft.y,0,0}
	,m_Vertices{}
{
	++m_Instances;
	if (m_Instances == 1)
	{
		m_pTexture = new Texture{ "Resources/Images/Platform.png" };
	}
	m_Shape.width = m_pTexture->GetWidth();
	m_Shape.height = m_pTexture->GetHeight();
	
	m_Vertices.push_back(bottomLeft);
	m_Vertices.push_back(Point2f{bottomLeft.x, bottomLeft.y + m_Shape.height});
	m_Vertices.push_back(Point2f{bottomLeft.x + m_Shape.width, bottomLeft.y + m_Shape.height});
	m_Vertices.push_back(Point2f{bottomLeft.x + m_Shape.width, bottomLeft.y});
	m_Vertices.push_back(bottomLeft);
}

Platform::~Platform()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void Platform::Draw() const
{
	m_pTexture->Draw(m_Shape);
}

void Platform::HandleCollision(Point2f& actorLoc, Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (actorVelocity.y > 0) return;
	HitInfo HI{};
	Point2f p1{ actorLoc.x + actorShape.width / 2,actorLoc.y + actorShape.height };
	Point2f p2{ actorLoc.x + actorShape.width / 2,actorLoc.y };
	if (Raycast(m_Vertices, p1, p2, HI))
	{
		actorLoc.y = HI.intersectPoint.y;
		actorVelocity.y = 0;
	}
}

bool Platform::IsOnground(const Point2f& actorLoc, const Rectf& actorShape, const Vector2f& velocity) const
{
	HitInfo HI{};
	if (velocity.y > 0) return false;
	else if (Raycast(m_Vertices, Point2f{actorLoc.x + actorShape.width / 2, actorLoc.y - 1}, Point2f{ actorLoc.x + actorShape.width / 2, actorLoc.y + actorShape.height * 0.9f}, HI))
	{
		return true;
	}
	return false;
}
