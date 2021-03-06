#include "pch.h"
#include "Level.h"
#include "Player.h"
#include "SVGParser.h"
#include "Texture.h"

#include "PickUpManager.h"
#include "FireFlower.h"
#include "Mushroom.h"
#include "Coin.h"

#include "KoopaBaseManager.h"
#include "Shell.h"
#include "Koopa.h"

#include "Platform.h"
#include "Mario.h"

#include "MysteryBoxManager.h"
#include "MysteryBox.h"

#include "CheckPoint.h"
#include "Endgoal.h"

#include "SoundManager.h"
#include "SoundStream.h"

using namespace utils;

Level::Level(Player& player)
	:m_EnableDebugDraw{false}
	,m_Player{player}
	,m_Vertices{}
	,m_pPickUpManager{new PickUpManager()}
	,m_pKoopaBaseManager{new KoopaBaseManager()}
	,m_pPlatforms{}
	,m_pBackgroundTexture{new Texture("Resources/Background.png")}
	,m_pLevelTexture{new Texture("Resources/Level.png")}
	,m_pMysteryBoxManager{new MysteryBoxManager()}
{
	m_pPlatforms.reserve(30);
	m_pPlatforms.reserve(30);

	KoopaBase::InitLevelRef(this);
	m_Vertices.push_back(std::vector<Point2f>{});
	if(!SVGParser::GetVerticesFromSvgFile("Resources/thirdAttempt.svg", m_Vertices)) throw "Something went wrong";
	ScaleLevel(m_Player.GetpMario()->m_Scale);
	PushPlatforms();
	m_pPickUpManager->PushPickUps();
	m_pKoopaBaseManager->PushKoopaBases();
	
	{
		using PuType = PickUp::Type;
		Push_back(new MysteryBox(Point2f{ 1066,168 }, new Coin(PuType::coin)));
		Push_back(new MysteryBox(Point2f{ 1120,168 }, new Mushroom(PuType::normalMushroom, this)));
		Push_back(new MysteryBox(Point2f{ 1480,150 }, new Coin(PuType::coin)));
		Push_back(new MysteryBox(Point2f{ 1515,150 }, new Coin(PuType::coin)));
		Push_back(new MysteryBox(Point2f{ 4980,150 }, new Coin(PuType::coin)));
		Push_back(new MysteryBox(Point2f{ 5010,150 }, new Coin(PuType::coin)));
		Push_back(new MysteryBox(Point2f{ 5040,150 }, new Coin(PuType::coin)));
	}


	m_pCheckPoints.push_back(new CheckPoint(Point2f{4486,84}));
	m_pCheckPoints.push_back(new Endgoal(Point2f{ 8421, 84 }));
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
	delete m_pLevelTexture;
	m_pLevelTexture = nullptr;

	delete m_pPickUpManager;
	m_pPickUpManager = nullptr;
	delete m_pKoopaBaseManager;
	m_pKoopaBaseManager = nullptr;
	delete m_pMysteryBoxManager;
	m_pMysteryBoxManager = nullptr;
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		m_Vertices[i].clear();
	}
	m_Vertices.clear();
	for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
	{
		delete m_pPlatforms[i];
		m_pPlatforms[i] = nullptr;
	}
	for (size_t i{ 0 }; i < m_pCheckPoints.size(); ++i)
	{
		delete m_pCheckPoints[i];
		m_pCheckPoints[i] = nullptr;
	}
}

void Level::Draw(const Point2f& cameraLoc, bool debugDraw) const
{
	glPushMatrix();
	{
		glScalef(2.5f, 2.5f, 1);
		for (int i{ 0 }; i < 8; ++i)
		{
			m_pBackgroundTexture->Draw(Point2f{ cameraLoc.x * 0.1f - 500 + i * m_pBackgroundTexture->GetWidth(),0});
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		glScalef(GameObject::m_Scale, GameObject::m_Scale, 1);
		m_pLevelTexture->Draw();
	}
	glPopMatrix();
	for (CheckPoint* checkPoint : m_pCheckPoints)
	{
		if (checkPoint)
		{
			checkPoint->Draw();
		}
	}
	m_pPickUpManager->Draw();
	m_pKoopaBaseManager->Draw();
	m_pMysteryBoxManager->Draw();
	//if (m_pKoopa) m_pKoopa->Draw();
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

void Level::UpdateContent(float elapsedSec, Mario* mario)
{
	if (mario->GetStage() == Mario::Stage::dead)
	{
		SoundStream* overworldTheme{ SoundManager::GetSoundStream("Resources/OverworldTheme.mp3") };
		if (overworldTheme->IsPlaying())
		{
			overworldTheme->Stop();
		}
		return;
	}
	else
	{
		SoundStream* overworldTheme{ SoundManager::GetSoundStream("Resources/OverworldTheme.mp3") };
		if (!overworldTheme->IsPlaying())
		{
			overworldTheme->Play(true);
		}
	}

	// Update PickUps
	m_pPickUpManager->Update(elapsedSec, &m_Player);
	// Update Shells and Koopas
	m_pKoopaBaseManager->Update(elapsedSec,&m_Player);
	// Update MysteryBoxes
	m_pMysteryBoxManager->Update(elapsedSec,&m_Player,m_pPickUpManager);
	// Update checkpoints
	for (CheckPoint* checkPoint : m_pCheckPoints)
	{
		if (checkPoint)
		{
			checkPoint->Update(elapsedSec, &m_Player);
		}
	}
}

void Level::Push_back(const Point2f& p)
{
	m_Vertices[0].push_back(p);
}

void Level::Push_back(Platform* p)
{
	m_pPlatforms.push_back(p);
}

void Level::Push_back(MysteryBox* m)
{
	m_pMysteryBoxManager->Push_back(m);
	Rectf rect{ m->GetRect() };
	m_pPlatforms.push_back(new Platform(Rectf{ rect.left,rect.bottom,16.f * GameObject::m_Scale,16.f * GameObject::m_Scale}));
}

void Level::Push_back(Shell* shell, const Point2f& point)
{
	m_pKoopaBaseManager->Push_back(shell, point);
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

bool Level::IsFullyOnTop(const Rectf& other, const Vector2f& velocity)
{
	HitInfo HI{};
	// This is the offset to determine how deep the raycast goes
	float downwardsOffSet{ 1 };
	// Faster falling = longer raycast (deeper in charachter)
	float upwardsOffset{ velocity.y / 50.0f };
	if (upwardsOffset < 8) upwardsOffset = 8;
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		bool firstCheck{ false };
		if (Raycast(m_Vertices[i], Point2f{ other.left,other.bottom + upwardsOffset }, Point2f{ other.left,other.bottom - downwardsOffSet }, HI))
		{
			firstCheck = true;
		}
		if (Raycast(m_Vertices[i], Point2f{ other.left + other.width,other.bottom + upwardsOffset }, Point2f{ other.left + other.width,other.bottom - downwardsOffSet }, HI))
		{
			return firstCheck;
		}
	}
	for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
	{
		if (!m_pPlatforms[i]) continue;
		else if (m_pPlatforms[i]->IsFullyOnTop(other))
		{
			return true;
		}
	}
	return false;
}

bool Level::IsHorizontallyTouching(const Rectf& other, HitInfo& hi, const Vector2f& velocity, float horDirection) const
{
	HitInfo HI{};
	const float velX{std::abs(velocity.x)};
	// This offset is to make sure that clipping vertically isn't seen as a touch
	float offsetBL{ 1 };
	// Sprinting = longer raycast (further out of charachter)
	float sidewaysOffset{ velX / 50.0f };
	if (sidewaysOffset < 1) sidewaysOffset = 1;
	// Raycast points
	Point2f leftTop{ other.left - sidewaysOffset,other.bottom + other.height };
	Point2f rightTop{ other.left + other.width + sidewaysOffset,other.bottom + other.height };
	Point2f leftBot{ other.left - sidewaysOffset,other.bottom + offsetBL };
	Point2f rightBot{ other.left + other.width + sidewaysOffset,other.bottom + offsetBL };
	if (horDirection >= 0.5f)
	{
		leftTop.x += other.width / 2;
		leftBot.x += other.width / 2;
	}
	else if (horDirection <= -0.5f)
	{
		rightTop.x -= other.width / 2;
		rightBot.x -= other.width / 2;
	}

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
	for (size_t i{ 0 }; i < m_pPlatforms.size(); ++i)
	{
		if (!m_pPlatforms[i]) continue;
		else if (m_pPlatforms[i]->IsHorizontallyTouching(other,HI,velocity,horDirection))
		{
			hi = HI;
			return true;
		}
	}
	return false;
}

bool Level::SwitchDebugDrawLevel()
{
	m_EnableDebugDraw = !m_EnableDebugDraw;
	return m_EnableDebugDraw;
}

float Level::GetFurthestXValue() const
{
	float highest{0};

	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		for (size_t j{ 0 }; j < m_Vertices[i].size(); ++j)
		{
			if (m_Vertices[i][j].x > highest) highest = m_Vertices[i][j].x;
		}
	}

	return highest;
}

void Level::ScaleLevel(float scale, int vectorAmount)
{
	size_t loopAmount{};
	if (vectorAmount <= -1) loopAmount = m_Vertices.size();
	else loopAmount = size_t(vectorAmount) ;
	for (int i{ 0 }; i < loopAmount; ++i)
	{
		for (int j{ 0 }; j < m_Vertices[i].size(); ++j)
		{
			m_Vertices[i][j].x *= scale;
			m_Vertices[i][j].y *= scale;
		}
	}
}

void Level::PushPlatforms()
{
	Push_back(new Platform(Point2f{ 535,165 }, 440, 1));
	Push_back(new Platform(Point2f{ 1235,195 }, 190, 1));

	Push_back(new Platform(Point2f{ 5240,165 }, 130, 1));
	Push_back(new Platform(Point2f{ 5295,250 }, 220, 1));
	Push_back(new Platform(Point2f{ 5460,165 }, 165, 1));

	Push_back(new Platform(Point2f{ 5938,220 }, 274, 1));
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
		m_pPickUpManager->Push_back(new Coin(Coin::Type::coin, Point2f{100 + 20 * i,200 }));
	}
	m_pPickUpManager->Push_back(new Mushroom(PickUp::Type::normalMushroom, this, Point2f{ 10,200 }));
}
