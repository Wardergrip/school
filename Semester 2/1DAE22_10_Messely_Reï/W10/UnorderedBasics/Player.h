#pragma once
#include <string>
#include <iostream>

class Player
{
public:
	explicit Player(const std::string& name, int score = 0 );
	void IncrementScore( int value );
	const std::string& GetName( ) const;
	int GetScore( ) const;

private:
	std::string m_Name;
	int m_Score;
};
std::ostream& operator<<( std::ostream& out, const Player& player );
std::ostream& operator<<( std::ostream& out, const std::pair<std::string, Player> & pair );

