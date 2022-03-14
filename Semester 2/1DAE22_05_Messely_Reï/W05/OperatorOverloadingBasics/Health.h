#pragma once

class Health final
{
public:
	Health( int value); 
	int GetValue( ) const;

	Health& operator+=(int value);
	Health& operator-=(int value);
	Health& operator+=(const Health& h);
	Health& operator-=(const Health& h);

private:
	int m_Value;
};

Health operator+(int value, const Health& health);
Health operator+(const Health& health, int value);
Health operator-(int value, const Health& health);
Health operator-(const Health& health, int value);
