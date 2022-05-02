#pragma once
#include <vector>
#include <iostream>
#include "Container.h"
#include <cassert>
// ------------------ Declarations
template<typename T>
T GetRandomElement( );

template<typename T>
Container<T> CreateContainer( int size, std::vector<T>& createdElements );

template<typename T>
void TestContainer( );

// ------------------ Definitions
template<typename T>
Container<T> CreateContainer( int size, std::vector<T>& createdElements )
{
	Container<T> container;
	for ( int nr{ 1 }; nr <= size; ++nr )
	{
		T randElement = GetRandomElement<T>( );
		createdElements.push_back( randElement );
		container.PushBack( randElement );
	}
	return container;
}

template<typename T>
void TestContainer( )
{
	Container<T> container1;
	std::vector<T> vector1;

	// PushBack elements and test size
	const int containerSize{ 20 };
	for (int nr{ 1 }; nr <= containerSize; ++nr)
	{
		T randElement = GetRandomElement<T>();
		vector1.push_back(randElement);
		if (nr % 2 == 0)
		{
			container1.PushBack(randElement);
		}
		else
		{
			container1.PushBack(std::move(randElement));
		}
		assert(container1.Size() == nr);
	}
	std::cout << "Test of PushBack and Size passed\n";

	// Test Get and Set
	for ( int idx{ 0 }; idx < containerSize; ++idx )
	{
		assert( container1.Get( idx ) == vector1[idx] );
		T randElement = GetRandomElement<T>( );
		vector1[idx] = randElement;
		if (idx % 2 == 0)
		{
			container1.Set(idx, randElement);
		}
		else
		{
			container1.Set(idx, std::move(randElement));
		}
		assert( container1.Get( idx ) == vector1[idx] );
	}
	std::cout << "Test of Get and Set passed\n";

	// Test operator[]
	for ( int idx{ 0 }; idx < containerSize; ++idx )
	{
		assert( container1[idx] == vector1[idx] );
		T randElement = GetRandomElement<T>( );
		vector1[idx] = container1[idx] = randElement;
		assert( container1[idx] == vector1[idx] );
	}
	std::cout << "Test of operator[] passed\n";

	// Initializer list 
	std::vector<T> vector4{ GetRandomElement<T>() ,GetRandomElement<T>() ,GetRandomElement<T>() };
	Container<T> container4{ vector4[0],vector4[1],vector4[2]};
	for (int idx{}; idx < int( vector4.size() ); ++idx)
	{
		assert(container4[idx] == vector4[idx]);
	}
	assert(container4.Size() == int(vector4.size()));
	std::cout << "Test of constructor with initializer_list passed\n";

}


