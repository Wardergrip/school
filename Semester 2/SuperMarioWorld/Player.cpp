#include "pch.h"
#include "Player.h"
#include <iostream>

#include "Mario.h"
#include "Level.h"
#include "XMLProcessor.h"
#include "SoundManager.h"

Player::Player()
	:m_pMario{nullptr}
{
	ResetAll();
}

Player::~Player()
{
	delete m_pMario;
	m_pMario = nullptr;
}

void Player::Draw() const
{
	m_pMario->Draw();
}

void Player::Update(float elapsedSec, Level& level)
{
	if (m_Time == 0) return;

	m_pMario->Update(elapsedSec, level);

	if (m_pMario->IsFullyDead())
	{
		if (!ReduceLive())
		{
			m_GameOver = true;
			std::cout << "Checking personalbest...\n";
			if (XMLProcessor::SavePersonalBest(ToXML()))
			{
				std::cout << "Saved new personal best\n";
			}
			else
			{
				std::cout << "Kept old personal best\n";
			}
		}
		else
		{
			m_SoftReset = true;
		}
	}

	m_Increment += elapsedSec;
	if (m_Increment >= 1)
	{
		m_Increment -= 1.f;
		--m_Time;
	}
}

void Player::ResetAll()
{
	if (m_pMario) delete m_pMario;

	m_Score = 0;
	m_Lives = 3;
	m_CoinAmount = 0;
	m_BigCoinAmount = 0;
	m_Increment = 0;
	m_Time = 300;
	m_LastCheckPointPos = Point2f{ 20, 300 };
	m_GameOver = false;
	m_SoftReset = false;

	m_pMario = new Mario();
	m_pMario->SetPosition(m_LastCheckPointPos);
}

void Player::SoftReset()
{
	if (m_pMario) delete m_pMario;
	m_pMario = new Mario();
	m_pMario->SetPosition(m_LastCheckPointPos);
	m_SoftReset = false;
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

unsigned int Player::GetTime() const
{
	return m_Time;
}

bool Player::IsGameOver() const
{
	return m_GameOver;
}

bool Player::IsSoftReset() const
{
	return m_SoftReset;
}

Mario* Player::GetpMario() const
{
	return m_pMario;
}

Rectf Player::GetMarioRect() const
{
	return m_pMario->GetRect();
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:
		if (m_pMario->Jump())
		{
			SoundManager::GetAndPlaySoundEffect("Resources/jumpSFX.ogg");
		}
		break;
	case SDLK_o:
		std::cout << "MarioPos [" << m_pMario->GetPureLocation().x << ", " << m_pMario->GetPureLocation().y << "]\n";
		break;
	}
}

void Player::DebugPrintAllStats() const
{
	std::cout << "Score: " << m_Score << '\n';
	std::cout << "Lives: " << m_Lives << '\n';
	std::cout << "Coins: " << m_CoinAmount << '\n';
	std::cout << "Dragon coins: " << m_BigCoinAmount << '\n';
}

void Player::SetLastCheckPointPos(const Point2f& pos)
{
	m_LastCheckPointPos = pos;
}

Point2f Player::GetLastCheckPointPos() const
{
	return m_LastCheckPointPos;
}

void Player::Win()
{
	std::cout << "You finished the game with\n"
		<< "Score: " << m_Score << '\n'
		<< "Lives: " << m_Lives << '\n'
		<< "Coins: " << m_CoinAmount << '\n'
		<< "Dragoncoins: " << m_BigCoinAmount << '\n'
		<< "With " << m_Time << " seconds left\n";
	
	std::cout << "Checking personalbest...\n";
	if (XMLProcessor::SavePersonalBest(ToXML()))
	{
		std::cout << "Saved new personal best\n";
	}
	else
	{
		std::cout << "Kept old personal best\n";
	}

	m_GameOver = true;
}

std::string Player::ToXML() const
{
	int lives{ (m_Lives < 0 ? 0 : m_Lives) };
	std::string output;
	std::string helper{ '\"' };
	output += "<personalbest\n";
	output += '\t'; // Horizontal tab
	output += "time=" + helper + std::to_string(m_Time) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "score=" + helper + std::to_string(m_Score) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "lives=" + helper + std::to_string(lives) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "coins=" + helper + std::to_string(m_CoinAmount) + helper + '\n';
	output += '\t'; // Horizontal tab
	output += "bigCoins=" + helper + std::to_string(m_BigCoinAmount) + helper + '\n';
	output += "/>";
	return output;
}
