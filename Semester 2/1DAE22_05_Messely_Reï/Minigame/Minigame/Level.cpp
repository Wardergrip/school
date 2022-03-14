#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "Camera.h"
#include "SVGParser.h"
#include "Platform.h"
using namespace utils;

Level::Level()
	:m_Vertices{}
	,m_pBackgroundTexture{ new Texture{"resources/images/background.png"} }
	,m_pFenceTexture{ new Texture{"resources/images/Fence.png"} }
	,m_FenceBottomLeft{200,190}
	,m_Boundaries{0,0,846, 500 }
	,m_pPlatform{ new Platform(Point2f{150,300}) }
	,m_pEndSignTexture{new Texture("Resources/images/EndSign.png")}
	,m_EndSignShape{ Rectf{730,224,m_pEndSignTexture->GetWidth(),m_pEndSignTexture->GetHeight()}}
	,m_EndReached{false}
{
	/*m_Vertices.push_back(Point2f{0,0});
	m_Vertices.push_back(Point2f{0,190});
	m_Vertices.push_back(Point2f{340,190});
	m_Vertices.push_back(Point2f{408,124});
	m_Vertices.push_back(Point2f{560,124});
	m_Vertices.push_back(Point2f{660,224});
	m_Vertices.push_back(Point2f{846,224});
	m_Vertices.push_back(Point2f{846,0});
	m_Vertices.push_back(Point2f{0,0});*/
	SVGParser::GetVerticesFromSvgFile("resources/images/level.svg", m_Vertices);
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
	delete m_pFenceTexture;
	m_pFenceTexture = nullptr;

	delete m_pPlatform;
	m_pPlatform = nullptr;

	delete m_pEndSignTexture;
	m_pEndSignTexture = nullptr;
}

void Level::DrawBackground() const
{
	if (m_pBackgroundTexture == nullptr) throw "Invalid texture path";
	m_pBackgroundTexture->Draw();
	m_pPlatform->Draw();
}

void Level::DrawForeground() const
{
	if (m_pFenceTexture == nullptr) throw "Invalid texture path";
	m_pFenceTexture->Draw(m_FenceBottomLeft);
	m_pEndSignTexture->Draw(m_EndSignShape);
}

void Level::HandleCollision(Point2f& actorLoc, Rectf& actorShape, Vector2f& actorVelocity) const
{
	HitInfo HI{};
	Point2f p1{ actorLoc.x + actorShape.width / 2,actorLoc.y + actorShape.height };
	Point2f p2{ actorLoc.x + actorShape.width / 2,actorLoc.y };
	if (Raycast(m_Vertices[0], p1, p2, HI))
	{
		actorLoc.y = HI.intersectPoint.y;
		actorVelocity.y = 0;
	}
	m_pPlatform->HandleCollision(actorLoc, actorShape, actorVelocity);
}

bool Level::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	HitInfo HI{};
	Point2f p1{ actorShape.left + actorShape.width / 2,actorShape.bottom + actorShape.height };
	Point2f p2{ actorShape.left + actorShape.width / 2,actorShape.bottom - 1};
	if (Raycast(m_Vertices[0], p1, p2, HI))
	{
		return true;
	}
	return m_pPlatform->IsOnground(Point2f{actorShape.left,actorShape.bottom},actorShape, actorVelocity);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& actorShape)
{
	m_EndReached = IsOverlapping(actorShape, m_EndSignShape);
	return m_EndReached;
}
