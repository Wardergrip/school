#pragma once
#include <string>
#include <iostream>

class Player
{
public:
	explicit Player( const std::string& surname, const std::string& firstName, int score = 0 );
	void IncrementScore( int value );
	std::string GetName( ) const;
	int GetScore( ) const;
	bool operator<(const  Player& rhs ) const;

private:
	std::string m_Surname;
	std::string m_FirstName;
	int m_Score;
};
std::ostream& operator<<( std::ostream& out, const Player& player );

