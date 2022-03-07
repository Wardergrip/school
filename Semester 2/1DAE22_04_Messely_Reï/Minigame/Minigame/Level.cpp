#include "pch.h"
#include "Level.h"
#include "Texture.h"
using namespace utils;

Level::Level()
	:m_Vertices{}
	,m_pBackgroundTexture{ new Texture{"resources/images/background.png"} }
	,m_pFenceTexture{ new Texture{"resources/images/Fence.png"}}
	,m_FenceBottomLeft{200,190}
{
	m_Vertices.push_back(Point2f{0,0});
	m_Vertices.push_back(Point2f{0,190});
	m_Vertices.push_back(Point2f{340,190});
	m_Vertices.push_back(Point2f{408,124});
	m_Vertices.push_back(Point2f{560,124});
	m_Vertices.push_back(Point2f{660,224});
	m_Vertices.push_back(Point2f{846,224});
	m_Vertices.push_back(Point2f{846,0});
	m_Vertices.push_back(Point2f{0,0});
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
	delete m_pFenceTexture;
	m_pFenceTexture = nullptr;
}

void Level::DrawBackground() const
{
	if (m_pBackgroundTexture == nullptr) throw "Invalid texture path";
	m_pBackgroundTexture->Draw();
}

void Level::DrawForeground() const
{
	if (m_pFenceTexture == nullptr) throw "Invalid texture path";
	m_pFenceTexture->Draw(m_FenceBottomLeft);
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	HitInfo HI{};
	Point2f p1{ actorShape.left + actorShape.width / 2,actorShape.bottom + actorShape.height };
	Point2f p2{ actorShape.left + actorShape.width / 2,actorShape.bottom };
	if (Raycast(m_Vertices, p1, p2, HI))
	{
		actorShape.bottom = HI.intersectPoint.y;
		actorVelocity.y = 0;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	HitInfo HI{};
	Point2f p1{ actorShape.left + actorShape.width / 2,actorShape.bottom + actorShape.height };
	Point2f p2{ actorShape.left + actorShape.width / 2,actorShape.bottom - 1};
	if (Raycast(m_Vertices, p1, p2, HI))
	{
		return true;
	}
	return false;
}
