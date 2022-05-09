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
#include "Shell.h"
#include "Koopa.h"
#include "MysteryBox.h"
#include "CheckPoint.h"
#include "Endgoal.h"
using namespace utils;
#include <iostream>

Level::Level(Player& player)
	:m_EnableDebugDraw{true}
	,m_Player{player}
	,m_Vertices{}
	,m_pPickUps{}
	,m_pPlatforms{}
	,m_pBackgroundTexture{new Texture("Resources/Background.png")}
	,m_pLevelTexture{new Texture("Resources/Level.png")}
	,m_pShells{}
	,m_pKoopas{}
	,m_pMysteryBoxes{}
{
	m_pPickUps.reserve(16);
	m_pPlatforms.reserve(30);
	m_pPlatforms.reserve(30);
	m_pShells.reserve(16);
	m_pKoopas.reserve(16);
	m_pMysteryBoxes.reserve(20);

	KoopaBase::InitLevelRef(this);
	m_Vertices.push_back(std::vector<Point2f>{});
	//PushDemoLevel();
	//PushDemoPickUps();
	if(!SVGParser::GetVerticesFromSvgFile("Resources/thirdAttempt.svg", m_Vertices)) throw "Something went wrong";
	ScaleLevel(m_Player.GetpMario()->m_Scale);
	PushPlatforms();
	PushPickups();

#pragma region FirstPlatform with Koopas
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red));
	m_pKoopas[0]->SetPosition(Point2f{ 570,166 });
	m_pKoopas[1]->SetPosition(Point2f{ 600,166 });
	m_pKoopas[2]->SetPosition(Point2f{ 630,166 });
	m_pKoopas[3]->SetPosition(Point2f{ 660,166 });
	m_pKoopas[4]->SetPosition(Point2f{ 680,166 });
	m_pKoopas[5]->SetPosition(Point2f{ 700,166 });
#pragma endregion

	m_pShells.push_back(new Shell(KoopaBase::Color::red));
	m_pShells[0]->SetPosition(Point2f{300,150});

	m_pShells.push_back(new Shell(KoopaBase::Color::red));
	m_pShells[1]->SetPosition(Point2f{ 2220,87 });
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::red, KoopaBase::Type::naked));
	m_pKoopas[6]->SetPosition(Point2f{ 2260,87 });
	m_pShells.push_back(new Shell(KoopaBase::Color::green));
	m_pShells[2]->SetPosition(Point2f{3024,87});
	m_pKoopas.push_back(new Koopa(KoopaBase::Color::green,KoopaBase::Type::naked));
	m_pKoopas[7]->SetPosition(Point2f{ 3050,87 });

	m_pMysteryBoxes.push_back(new MysteryBox(Point2f{ 1066,168 }, new Coin(PickUp::Type::coin)));
	m_pPlatforms.push_back(new Platform(Rectf{ 1066,168,16.f * GameObject::m_Scale,16.f * GameObject::m_Scale }));
	m_pMysteryBoxes.push_back(new MysteryBox(Point2f{ 1120,168 }, new Mushroom(PickUp::Type::normalMushroom, this)));
	m_pPlatforms.push_back(new Platform(Rectf{ 1120,168,16.f * GameObject::m_Scale,16.f * GameObject::m_Scale }));

	m_pCheckPoints.push_back(new CheckPoint(Point2f{4486,84}));
	m_pCheckPoints.push_back(new Endgoal(Point2f{ 8421, 84 }));
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	m_pBackgroundTexture = nullptr;
	delete m_pLevelTexture;
	m_pLevelTexture = nullptr;

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
	for (size_t i{ 0 }; i < m_pShells.size(); ++i)
	{
		delete m_pShells[i];
		m_pShells[i] = nullptr;
	}
	for (size_t i{ 0 }; i < m_pKoopas.size(); ++i)
	{
		delete m_pKoopas[i];
		m_pKoopas[i] = nullptr;
	}
	for (size_t i{ 0 }; i < m_pMysteryBoxes.size(); ++i)
	{
		delete m_pMysteryBoxes[i];
		m_pMysteryBoxes[i] = nullptr;
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
	for (CheckPoint* c : m_pCheckPoints)
	{
		if (c) c->Draw();
	}
	DrawPickUps();
	for (Koopa* k : m_pKoopas)
	{
		if (k) k->Draw();
	}
	for (Shell* s : m_pShells)
	{
		if (s) s->Draw();
	}
	for (MysteryBox* m : m_pMysteryBoxes)
	{
		if (m) m->Draw();
	}
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

void Level::DrawPickUps() const
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] == nullptr) continue;
		m_pPickUps[i]->Draw();
	}
}

void Level::UpdateContent(float elapsedSec, Mario* mario)
{
	// CLEANUP
	//for (size_t i{ 0 }; i < m_pShells.size(); ++i)
	//{
	//	//std::cout << "Shell[" << i << "] :" << m_pShells[i] << '\n';
	//	if (m_pShells[i] == nullptr) continue;
	//	else if (m_pShells[i]->GetYPos() < -300)
	//	{
	//		//std::cout << "Cleaning up shell idx " << i << '\n';
	//		delete m_pShells[i];
	//		m_pShells[i] = nullptr;
	//	}
	//}
	if (mario->GetStage() == Mario::Stage::dead) return;
	// Update PickUps
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
	// Update Shells
	if (m_Player.GetpMario()->IsTryingToThrowShell())
	{
		Push_back(m_Player.GetpMario()->GiveShell());
	}
	for (size_t i{0}; i < m_pShells.size(); ++i)
	{
		if (m_pShells[i] == nullptr) continue;
		m_pShells[i]->Update(elapsedSec, m_Player);
		if (m_pShells[i]->IsGrabbed())
		{
			if (m_Player.GetpMario()->GetShell())
			{
				m_pShells[i]->SetGrabbed(false);
				m_pShells[i]->Kick(m_Player.GetpMario()->GetHorDirection());
			}
			else
			{
				m_Player.GetpMario()->SetShell(m_pShells[i]);
				m_pShells[i] = nullptr;
				continue;
			}
		}
		m_pShells[i]->UpdateShellCollisions(m_pShells);
		int j{ m_pShells[i]->UpdateShellKoopaCollisions(m_pKoopas) };
		if (j == -1) continue;
		if (m_pShells[i]->IsGoingIn())
		{
			m_pKoopas[j]->SetShell(m_pShells[i]);
			m_pShells[i] = nullptr;
		}
	}
	// Update Koopas
	for (size_t i{ 0 }; i < m_pKoopas.size(); ++i)
	{
		if (m_pKoopas[i] == nullptr) continue;
		m_pKoopas[i]->Update(elapsedSec, m_Player);
		if (m_pKoopas[i]->IsDead())
		{
			delete m_pKoopas[i];
			m_pKoopas[i] = nullptr;
		}
		else if (m_pKoopas[i]->IsWantingToGiveShell())
		{
			bool isPointerPushed{ false };
			for (size_t i{ 0 }; i < m_pShells.size(); ++i)
			{
				if (m_pShells[i] != nullptr) continue;
				if (m_pKoopas[i]->GetShell() == nullptr) continue;
				if (isPointerPushed) continue;
				m_pShells[i] = m_pKoopas[i]->GiveShell();
				isPointerPushed = true;
			}
			if (!isPointerPushed)
			{
				m_pShells.push_back(m_pKoopas[i]->GiveShell());
			}
		}
	}
	// Update MysteryBoxes
	for (size_t i{ 0 }; i < m_pMysteryBoxes.size(); ++i)
	{
		m_pMysteryBoxes[i]->Update(elapsedSec);
		if (m_pMysteryBoxes[i]->IsOverlappingBottomHitbox(m_Player.GetpMario()->GetRect()))
		{
			m_pMysteryBoxes[i]->Bump();
			m_Player.GetpMario()->BumpHead();
		}
		if (m_pMysteryBoxes[i]->IsWantingToGivePickUp())
		{
			if (m_pMysteryBoxes[i]->GetPickUp()->GetType() == PickUp::Type::coin)
			{
				delete m_pMysteryBoxes[i]->GivePickUp();
			}
			else Push_back(m_pMysteryBoxes[i]->GivePickUp());
		}
	}
	// Update checkpoints
	for (CheckPoint* c : m_pCheckPoints)
	{
		if (c) c->Update(elapsedSec,&m_Player);
	}
}

void Level::Push_back(const Point2f& p)
{
	m_Vertices[0].push_back(p);
}

void Level::Push_back(PickUp* pu)
{
	bool isPointerPushed{ false };
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] != nullptr) continue;
		m_pPickUps[i] = pu;
		isPointerPushed = true;
	}
	if (!isPointerPushed) m_pPickUps.push_back(pu);
}

void Level::Push_back(Platform* p)
{
	m_pPlatforms.push_back(p);
}

void Level::Push_back(Shell* s)
{
	bool isPointerPushed{ false };
	for (size_t i{ 0 }; i < m_pShells.size(); ++i)
	{
		if (m_pShells[i] != nullptr) continue;
		if (isPointerPushed) continue;
		m_pShells[i] = s;
		isPointerPushed = true;
	}
	if (!isPointerPushed) m_pShells.push_back(s);
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

void Level::PushPickups()
{
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 2157,170 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 2184,200 }));
	Push_back(new Coin(PickUp::Type::bigCoin, Point2f{ 2212,205 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 2240,195 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 2267,170 }));

	Push_back(new Coin(PickUp::Type::bigCoin, Point2f{ 3024,206 }));

	Push_back(new Coin(PickUp::Type::coin, Point2f{ 4004,280 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 4032,310 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 4065,310 }));
	Push_back(new Coin(PickUp::Type::bigCoin, Point2f{ 4090,320 }));

	Push_back(new Coin(PickUp::Type::coin, Point2f{ 6020,306 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 6051,306 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 6076,306 }));
	Push_back(new Coin(PickUp::Type::bigCoin, Point2f{ 6130,310 }));

	Push_back(new Coin(PickUp::Type::coin, Point2f{ 7980,130 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 8000,160 }));
	Push_back(new Coin(PickUp::Type::coin, Point2f{ 8020,200 }));
	for (float i{ 0 }; i < 10; ++i)
	{
		Push_back(new Coin(PickUp::Type::coin, Point2f{ 8050 + i*30,220 }));
	}
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
		Push_back(new Coin(Coin::Type::coin, Point2f{100 + 20 * i,200 }));
	}
	Push_back(new Mushroom(PickUp::Type::normalMushroom, this, Point2f{ 10,200 }));
}
