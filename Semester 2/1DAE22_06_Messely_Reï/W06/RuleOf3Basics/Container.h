#pragma once

class Container final
{
public:
	explicit Container( int capacity  = 10); 
	Container(const Container& c);
	Container& operator=(const Container& c);
	~Container( );

	int Size( ) const;
	int Capacity( ) const;
	int Get( int index ) const;
	void Set( int index, int value );
	void PushBack( int element );

	//int operator[](int index) const; // first version (only get)
	int& operator[](int index) ; // second version (get and set)
	int operator[](int index) const; // necessary to have a non modifying []
	// If the value type is known to be a built-in type, 
	// the const variant should return by value.

private:
	int m_Size;
	int m_Capacity;
	int *m_pElement;

	void Reserve( int newCapacity );
};
