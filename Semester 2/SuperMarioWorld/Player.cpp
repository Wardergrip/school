#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player()
	:m_Score{0}
	,m_Lives{3}
	,m_CoinAmount{0}
	,m_BigCoinAmount{0}
{
}

void Player::AddScore(unsigned int score)
{
	m_Score += score;
}

void Player::AddLife()
{
	++m_Lives;
}

void Player::AddCoin()
{
	++m_CoinAmount;
	if (m_CoinAmount >= 100)
	{
		m_CoinAmount = 0;
		AddLife();
	}
	AddScore(200);
}

void Player::AddBigCoin()
{
	++m_BigCoinAmount;
	switch (m_BigCoinAmount)
	{
	case 1:
		AddScore(1000);
		break;
	case 2:
		AddScore(2000);
		break;
	case 3:
		AddScore(4000);
		break;
	case 4:
		AddScore(8000);
		break;
	case 5:
		AddLife();
		break;
	}
}

bool Player::ReduceLive()
{
	--m_Lives;
	if (m_Lives < 0) return false;
	return true;
}

unsigned int Player::GetScore() const
{
	return m_Score;
}

int Player::GetLives() const
{
	return m_Lives;
}

int Player::GetCoinAmount() const
{
	return m_CoinAmount;
}

void Player::DebugPrintAll() const
{
	std::cout << "Score: " << m_Score << '\n';
	std::cout << "Lives: " << m_Lives << '\n';
	std::cout << "Coins: " << m_CoinAmount << '\n';
	std::cout << "Dragon coins: " << m_BigCoinAmount << '\n';
}
