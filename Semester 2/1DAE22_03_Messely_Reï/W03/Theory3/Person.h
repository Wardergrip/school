#pragma once
#include <string>

class Person
{
public:
	Person(const std::string& firstName, 
		const std::string& lastName);
	~Person();
	void Identify()const;
protected:
	std::string GetName() const;

private:
	std::string m_FirstName, m_LastName;	
};

