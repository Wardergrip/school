#include "pch.h"
#include "Level.h"

#include "FireFlower.h"
#include "Mushroom.h"
#include "Coin.h"
using namespace utils;

Level::Level()
	:m_Vertices{}
	,m_PickUps{}
{
	PushDemoLevel();
	PushDemoPickUps();
}

Level::~Level()
{
	m_Vertices.clear();
	for (size_t i{0}; i < m_PickUps.size(); ++i)
	{
		delete m_PickUps[i];
		m_PickUps[i] = nullptr;
	}
}

void Level::DebugDraw(const Color4f& col) const
{
	SetColor(col);
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if ((i + 1) < m_Vertices.size())
		{
			DrawLine(m_Vertices[i], m_Vertices[i + 1]);
		}
	}
}

void Level::DrawPickUps() const
{
	for (size_t i{ 0 }; i < m_PickUps.size(); ++i)
	{
		if (m_PickUps[i] == nullptr) continue;
		m_PickUps[i]->Draw();
	}
}

void Level::UpdatePickUps(float elapsedSec, const Rectf& other)
{
	for (size_t i{ 0 }; i < m_PickUps.size(); ++i)
	{
		if (m_PickUps[i] == nullptr) continue;
		m_PickUps[i]->Update(elapsedSec);
		if (m_PickUps[i]->IsOverlapping(other))
		{
			m_PickUps[i]->GetType();
			delete m_PickUps[i];
			m_PickUps[i] = nullptr;
		}
	}
}

void Level::Push_back(const Point2f& p)
{
	m_Vertices.push_back(p);
}

void Level::Push_back(PickUp* pu)
{
	m_PickUps.push_back(pu);
}

bool Level::IsOnTop(Rectf& other)
{
	HitInfo HI{};
	// How deep does the ray go under the shape
	float offSet{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + other.height / 2 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		// Following line may induce jitters
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + other.height / 2 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	return false;
}

bool Level::IsOnTop(const Rectf& other, HitInfo& hi)
{
	HitInfo HI{};
	float offSet{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + other.height / 2 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		hi = HI;
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + other.height / 2 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		hi = HI;
		return true;
	}
	return false;
}

bool Level::IsHorizontallyTouching(const Rectf& other) const
{
	HitInfo HI{};
	// This offset is to make sure that clipping vertically isn't seen as a touch
	float offsetBL{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left - 1,other.bottom + offsetBL}, Point2f{ other.left + other.width + 1,other.bottom + offsetBL}, HI))
	{
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left - 1,other.bottom + other.height }, Point2f{ other.left + other.width + 1,other.bottom + other.height }, HI))
	{
		return true;
	}
	return false;
}

void Level::PushDemoLevel()
{
	Push_back(Point2f{ 0,0 });
	Push_back(Point2f{ 0,100 });
	Push_back(Point2f{ 200,100 });
	Push_back(Point2f{ 200,10 });
	Push_back(Point2f{ 400,10 });
	Push_back(Point2f{ 400,100 });
	Push_back(Point2f{ 638,100 });
	Push_back(Point2f{ 638,0 });
	Push_back(Point2f{ 558,0 });
	Push_back(Point2f{ 0,0 });
}

void Level::PushDemoPickUps()
{
	for (float i{ 0 }; i < 10; ++i)
	{
		Push_back(new Coin(Coin::Type::normal, Point2f{100 + 20 * i,100 }));
	}
	Push_back(new Mushroom(PickUp::PickUpType::normalMushroom, this, Point2f{ 10,200 }));
}
