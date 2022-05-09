#include "pch.h"
#include "Player.h"
#include <sstream>


Player::Player( const std::string& name,int score )
	:m_Name(name )
	,m_Score{score}
{
}

void Player::IncrementScore( int value )
{
	m_Score += value;
}

const std::string& Player::GetName( ) const
{
	return m_Name;
}

int Player::GetScore( ) const
{
	return m_Score;
}

std::ostream& operator<<( std::ostream& out, const Player& player )
{
	std::stringstream ss;
	ss << "Player[" << player.GetName( ) << ", " << player.GetScore() << "] ";
	out << ss.str();
	return out;
}

std::ostream& operator<<( std::ostream& out, const std::pair<std::string, Player> & pair )
{
	out << pair.second;
	return out;
}



