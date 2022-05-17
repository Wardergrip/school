#include "pch.h"
#include "MysteryBoxManager.h"
#include "MysteryBox.h"
#include "PickUpManager.h"
#include "PickUp.h"
#include "Player.h"
#include "Mario.h"

MysteryBoxManager::MysteryBoxManager()
{
}

MysteryBoxManager::~MysteryBoxManager()
{
	for (size_t i{ 0 }; i < m_pMysteryBoxes.size(); ++i)
	{
		delete m_pMysteryBoxes[i];
		m_pMysteryBoxes[i] = nullptr;
	}
}

void MysteryBoxManager::Draw() const
{
	for (MysteryBox* mysterybox : m_pMysteryBoxes)
	{
		if (mysterybox)
		{
			mysterybox->Draw();
		}
	}
}

void MysteryBoxManager::Update(float elapsedSec, Player* player, PickUpManager* pickupmanager)
{
	for (size_t i{ 0 }; i < m_pMysteryBoxes.size(); ++i)
	{
		m_pMysteryBoxes[i]->Update(elapsedSec);

		if (m_pMysteryBoxes[i]->IsOverlappingBottomHitbox(player->GetpMario()->GetRect()))
		{
			m_pMysteryBoxes[i]->Bump();
			player->GetpMario()->BumpHead();
		}
		if (m_pMysteryBoxes[i]->IsWantingToGivePickUp())
		{
			if (m_pMysteryBoxes[i]->GetPickUp()->GetType() == PickUp::Type::coin)
			{
				delete m_pMysteryBoxes[i]->GivePickUp();
				player->AddCoin();
			}
			else
			{
				switch (m_pMysteryBoxes[i]->GetPickUp()->GetType())
				{
				case PickUp::Type::normalMushroom:
					player->AddScore(100);
					break;
				}
				pickupmanager->Push_back(m_pMysteryBoxes[i]->GivePickUp());
			}
		}
	}
}

void MysteryBoxManager::Push_back(MysteryBox* m)
{
	m_pMysteryBoxes.push_back(m);
}
