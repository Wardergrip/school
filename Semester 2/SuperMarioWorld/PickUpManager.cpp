#include "pch.h"
#include "PickUpManager.h"
#include "PickUp.h"
#include "Player.h"
#include "Mario.h"
#include "Coin.h"

PickUpManager::PickUpManager()
	:m_pPickUps{16}
{
}

PickUpManager::~PickUpManager()
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		delete m_pPickUps[i];
		m_pPickUps[i] = nullptr;
	}
}

void PickUpManager::Draw() const
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] == nullptr)
		{
			continue;
		}
		m_pPickUps[i]->Draw();
	}
}

void PickUpManager::Update(float elapsedSec, Player* player)
{
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if (m_pPickUps[i] == nullptr)
		{
			continue;
		}
		m_pPickUps[i]->Update(elapsedSec);
		if (m_pPickUps[i]->IsOverlapping(player->GetpMario()->GetRect()))
		{
			PickUp::Type t{ m_pPickUps[i]->GetType() };
			switch (t)
			{
			case PickUp::Type::coin:
				player->AddCoin();
				break;
			case PickUp::Type::bigCoin:
				player->AddBigCoin();
				break;
			case PickUp::Type::normalMushroom:
				player->GetpMario()->Grow();
				break;
			}
			delete m_pPickUps[i];
			m_pPickUps[i] = nullptr;
		}
	}
}

void PickUpManager::Push_back(PickUp* pickup)
{
	bool isPointerPushed{ false };
	for (size_t i{ 0 }; i < m_pPickUps.size(); ++i)
	{
		if ((m_pPickUps[i] != nullptr) || (isPointerPushed))
		{
			continue;
		}
		m_pPickUps[i] = pickup;
		isPointerPushed = true;
	}
	if (!isPointerPushed)
	{
		m_pPickUps.push_back(pickup);
	}
}

void PickUpManager::PushPickUps()
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
		Push_back(new Coin(PickUp::Type::coin, Point2f{ 8050 + i * 30,220 }));
	}
}
