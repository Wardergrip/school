#include "pch.h"
#include "Player.h"

Player::Player()
	:m_Score{0}
	,m_Lives{3}
	,m_CoinAmount{0}
{
}

void Player::AddScore(unsigned int score)
{
	m_Score += score;
}

void Player::AddLive()
{
	++m_Lives;
}

void Player::AddCoin()
{
	++m_CoinAmount;
	if (m_CoinAmount >= 100)
	{
		m_CoinAmount = 0;
		AddLive();
	}
}

bool Player::ReduceLive()
{
	if (m_Lives <= 0) return false;
	--m_Lives;
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
