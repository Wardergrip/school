#include "pch.h"
#include "Level.h"
#include "Player.h"
#include "SVGParser.h"
#include "Texture.h"

#include "FireFlower.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Platform.h"
#include "Mario.h"
using namespace utils;
#include <iostream>

Level::Level(Player& player)
	:m_EnableDebugDraw{true}
	,m_Player{player}
	,m_Vertices{}
	,m_pPickUps{}
	,m_pPlatforms{}
	,m_pBackgroundTexture{new Texture("Resources/Background.png")}
{
	m_Vertices.push_back(std::vector<Point2f>{});
	//PushDemoLevel();
	if(!SVGParser::GetVerticesFromSvgFile("Resources/firstPlatformE.svg", m_Vertices)) throw "Something went wrong";
	PushDemoPickUps();
}

Level::~Level()
{
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		m_Vertices[i].clear();
	}
	m_Vertices.clear();
	for (size_t i{0}; i < m_pPickUps.size(); ++i)
	{
		delete m_pPickUps[i];
		m_pPickUps[i] = nullptr;
	}
	for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
	{
		delete m_pPlatforms[i];
		m_pPlatforms[i] = nullptr;
	}
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
}

void Level::Draw(const Point2f& cameraLoc, bool debugDraw) const
{
	glPushMatrix();
	{
		glScalef(2.5f, 2.5f, 1);
		for (int i{ 0 }; i < 8; ++i)
		{
			m_pBackgroundTexture->Draw(Point2f{ -cameraLoc.x * 0.05f - 100 + i * m_pBackgroundTexture->GetWidth(),0});
		}
	}
	glPopMatrix();

	DrawPickUps();
	if (debugDraw) DebugDraw(Color4f{1,0,0,1},2.f);
}

void Level::DebugDraw(const Color4f& col, float lineThickness) const
{
	if (!m_EnableDebugDraw) return;
	SetColor(col);
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		for (size_t j{ 0 }; j < m_Vertices[i].size(); ++j)
		{
			if ((j + 1) < m_Vertices[i].size())
			{
				DrawLine(m_Vertices[i][j], m_Vertices[i][j + 1], lineThickness);
			}
		}
	}
	for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
	{
		if (!m_pPlatforms[i]) continue;
		m_pPlatforms[i]->DebugDraw(col, lineThickness);
	}
}

void Level::DrawPickUps() const
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] == nullptr) continue;
		m_pPickUps[i]->Draw();
	}
}

void Level::UpdatePickUps(float elapsedSec, Mario* mario)
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] == nullptr) continue;
		m_pPickUps[i]->Update(elapsedSec);
		if (m_pPickUps[i]->IsOverlapping(mario->GetRect()))
		{
			PickUp::Type t{ m_pPickUps[i]->GetType() };
			switch (t)
			{
			case PickUp::Type::coin:
				m_Player.AddCoin();
				break;
			case PickUp::Type::bigCoin:
				m_Player.AddBigCoin();
				break;
			case PickUp::Type::normalMushroom:
				mario->Grow();
				break;
			}
			delete m_pPickUps[i];
			m_pPickUps[i] = nullptr;
		}
	}
}

void Level::Push_back(const Point2f& p)
{
	m_Vertices[0].push_back(p);
}

void Level::Push_back(PickUp* pu)
{
	m_pPickUps.push_back(pu);
}

void Level::Push_back(Platform* p)
{
	m_pPlatforms.push_back(p);
}

bool Level::IsOnTop(Rectf& other)
{
	HitInfo HI{};
	// How deep does the ray go under the shape
	float offSet{ 1 };
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if (Raycast(m_Vertices[i], Point2f{other.left,other.bottom + 6}, Point2f{other.left,other.bottom - offSet}, HI))
		{
			// Following line may induce jitters
			other.bottom += offSet * (1 - HI.lambda);
			return true;
		}
		else if (Raycast(m_Vertices[i], Point2f{other.left + other.width,other.bottom + 6}, Point2f{other.left + other.width,other.bottom - offSet}, HI))
		{
			other.bottom += offSet * (1 - HI.lambda);
			return true;
		}
	}

		for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
		{
			if (!m_pPlatforms[i]) continue;
			else if (m_pPlatforms[i]->IsOnTop(other)) return true;
		}
	return false;
}

bool Level::IsOnTop(const Rectf& other, HitInfo& hi, const Vector2f& velocity)
{
	HitInfo HI{};
	// This is the offset to determine how deep the raycast goes
	float downwardsOffSet{ 1 };
	// Faster falling = longer raycast (deeper in charachter)
	float upwardsOffset{velocity.y / 50.0f};
	if (upwardsOffset < 8) upwardsOffset = 8;
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if (Raycast(m_Vertices[i], Point2f{other.left,other.bottom + upwardsOffset}, Point2f{other.left,other.bottom - downwardsOffSet}, HI))
		{
			hi = HI;
			return true;
		}
		else if (Raycast(m_Vertices[i], Point2f{other.left + other.width,other.bottom + upwardsOffset }, Point2f{other.left + other.width,other.bottom - downwardsOffSet}, HI))
		{
			hi = HI;
			return true;
		}
	}
	for (size_t i{0}; i < m_pPlatforms.size(); ++i)
	{
		if (!m_pPlatforms[i]) continue;
		else if (m_pPlatforms[i]->IsOnTop(other,HI))
		{
			hi = HI;
			return true;
		}
	}
	return false;
}

bool Level::IsHorizontallyTouching(const Rectf& other, HitInfo& hi, const Vector2f& velocity) const
{
	HitInfo HI{};
	const float velX{std::abs(velocity.x)};
	// This offset is to make sure that clipping vertically isn't seen as a touch
	float offsetBL{ 1 };
	// Sprinting = longer raycast (further out of charachter)
	float sidewaysOffset{ velX / 30.0f };
	if (sidewaysOffset < 1) sidewaysOffset = 1;
	// Raycast points
	Point2f leftTop{ other.left - sidewaysOffset,other.bottom + other.height }, rightTop{ other.left + other.width + sidewaysOffset,other.bottom + other.height };
	Point2f leftBot{ other.left - sidewaysOffset,other.bottom + offsetBL }, rightBot{ other.left + other.width + sidewaysOffset,other.bottom + offsetBL };

	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if (Raycast(m_Vertices[i], leftBot, rightBot, HI))
		{
			hi = HI;
			return true;
		}
		else if (Raycast(m_Vertices[i], leftTop, rightTop, HI))
		{
			hi = HI;
			return true;
		}
	}
	return false;
}

float Level::GetFurthestXValue()
{
	float highest{};

	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		for (size_t j{ 0 }; j < m_Vertices[i].size(); ++j)
		{
			if (m_Vertices[i][j].x > highest) highest = m_Vertices[i][j].x;
		}
	}

	return highest;
}

void Level::PushDemoLevel()
{
	Push_back(Point2f{ 0,0 });
	Push_back(Point2f{ 0,100 });
	Push_back(Point2f{ 200,100 });
	Push_back(Point2f{ 200,10 });
	Push_back(Point2f{ 400,10 });
	Push_back(Point2f{ 400,100 });
	Push_back(Point2f{ 1800,100 });
	Push_back(Point2f{ 1800,0 });
	Push_back(Point2f{ 558,0 });
	Push_back(Point2f{ 0,0 });
	Push_back(new Platform(Point2f{250,150},100));
}

void Level::PushDemoPickUps()
{
	for (float i{ 0 }; i < 10; ++i)
	{
		Push_back(new Coin(Coin::Type::coin, Point2f{100 + 20 * i,100 }));
	}
	Push_back(new Mushroom(PickUp::Type::normalMushroom, this, Point2f{ 10,200 }));
}
