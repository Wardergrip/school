#include "pch.h"
#include "PowerUpManager.h"
#include "SoundEffect.h"
#include "utils.h"
using namespace utils;

PowerUpManager::PowerUpManager()
	:m_pItems{}
	,m_pPickUpSE{new SoundEffect("Resources/Sounds/powerUp.mp3")}
{
}

PowerUpManager::~PowerUpManager()
{
	for (size_t i {0}; i < m_pItems.size(); ++i)
	{
		delete m_pItems[i];
		m_pItems[i] = nullptr;
	}
	m_pItems.clear();
	delete m_pPickUpSE;
	m_pPickUpSE = nullptr;
	// Memory leak is from pManager in game.cpp
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* p{ new PowerUp{ center, type } };
	m_pItems.push_back(p);
	return p;
}

void PowerUpManager::Update(float elapsedSec)
{
	for (size_t i{ 0 }; i < m_pItems.size(); ++i)
	{
		m_pItems[i]->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (size_t i{ 0 }; i < m_pItems.size(); ++i)
	{
		m_pItems[i]->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	for (size_t i{ 0 }; i < m_pItems.size(); ++i)
	{
		if (m_pItems[i]->IsOverlapping(rect))
		{
			delete m_pItems[i];
			m_pItems[i] = m_pItems.back();
			m_pItems.pop_back();
			m_pPickUpSE->Play(1);
			return true;
		}
	}
	return false;
}
