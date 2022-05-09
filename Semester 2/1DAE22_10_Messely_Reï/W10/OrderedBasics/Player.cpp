#include "pch.h"
#include "Player.h"
#include <algorithm>

Player::Player( const std::string& surname, const std::string& firstName, int score  )
	:m_Surname(surname )
	,m_FirstName(firstName )
	,m_Score{score}
{
}

void Player::IncrementScore( int value )
{
	m_Score += value;
}

std::string Player::GetName( ) const
{
	return m_Surname + " " + m_FirstName;
}

int Player::GetScore( ) const
{
	return m_Score;
}

bool Player::operator<( const  Player& rhs ) const
{
	return this->GetScore() < rhs.GetScore();
}

std::ostream& operator<<( std::ostream& out, const Player& player )
{
	out << player.GetName( );
	out << " (" << player.GetScore( ) << ")";
	return out;
}



