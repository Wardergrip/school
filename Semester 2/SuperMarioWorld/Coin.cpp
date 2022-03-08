#include "pch.h"
#include "Coin.h"
#include "Texture.h"
#include <iostream>

Texture* Coin::m_NormalCoinTexture{ nullptr };
Texture* Coin::m_BigCoinTexture{ nullptr };
int Coin::m_Instances{0};

Coin::Coin(Type type, const Point2f& spawnPos)
	:PickUp(type, nullptr, 3, 0.15f)
	,m_AnimGoingUp{ true }
{
	if (type != Type::coin && type != Type::bigCoin) throw "Wrong coin type!";
	m_Position = spawnPos;
	++m_Instances;
	if (m_Instances == 1)
	{
		m_NormalCoinTexture = new Texture{ "Resources/NormalCoin.png" };
		m_BigCoinTexture = new Texture{ "Resources/BigCoin.png" };
	}
	switch (type)
	{
	case Coin::Type::coin:
		m_pTexture = m_NormalCoinTexture;
		AdjustRectToTexture(3, 0.15f);
		break;
	case Coin::Type::bigCoin:
		m_pTexture = m_BigCoinTexture;
		AdjustRectToTexture(4, 0.75f);
		break;
	}
}

Coin::~Coin()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_NormalCoinTexture;
		m_NormalCoinTexture = nullptr;
		delete m_BigCoinTexture;
		m_BigCoinTexture = nullptr;
	}
	m_pTexture = nullptr;
}

void Coin::UpdateAnim(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_MaxSec)
	{
		if (m_AnimGoingUp) ++m_ActFrame;
		else --m_ActFrame;
		if (!(m_ActFrame % (m_Frames-1))) m_AnimGoingUp = false;
		if (m_ActFrame <= 0) m_AnimGoingUp = true;
		m_AccuSec = 0;
	}
	m_Rect.left = m_ActFrame * m_Rect.width;
}
