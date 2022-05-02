#pragma once
#include <initializer_list>
#include "pch.h"
#include "Container.h"
#include <cassert>
#include <iostream>

template <typename T>
class Container
{
public:
	explicit Container( int capacity = 10); 
	Container(const std::initializer_list<T>& list);
	Container( const Container& other );
	Container& operator=( const Container& other );
	Container( Container&& other )noexcept;           
	Container& operator=( Container&& other )noexcept;
	~Container( );

	int Size( ) const;
	int Capacity( ) const;
	T Get( int index ) const;
	void Set( int index, const T& value );
	void PushBack( const T& element );
	T& operator[]( int index ); 
	const T& operator[]( int index ) const;

private:
	int m_Size;
	int m_Capacity;
	T *m_pElements;

	void Reserve( int newCapacity );
};

// Function definitions

template <typename T>
Container<T>::Container(int capacity)
	: m_Size{ 0 }
	, m_Capacity{ capacity }
	, m_pElements{ new T[capacity] }
{
}
template <typename T>
Container<T>::Container(const std::initializer_list<T>& list)
	:m_Size{0}
	,m_Capacity{int(list.size())}
	,m_pElements{new T[list.size()]}
{
	for (const T& element : list)
	{
		PushBack(element);
	}
}
template <typename T>
Container<T>::Container(const Container& other)
	: m_Size{ 0 }
	, m_Capacity{ other.m_Capacity }
	, m_pElements{ new T[other.m_Capacity] }
{
	// Copy the elements
	for (int idx{}; idx < other.m_Size; ++idx)
	{
		PushBack(other[idx]);
	}
}
template <typename T>
Container<T>& Container<T>::operator=(const Container<T>& other)
{
	if (this != &other)// no self assignment
	{
		// Delete dyn allocated memory and create new
		delete[] m_pElements;
		m_pElements = new T[other.m_Capacity];
		m_Capacity = other.m_Capacity;
		m_Size = 0;

		// Copy the elements
		for (int idx{}; idx < other.m_Size; ++idx)
		{
			PushBack(other[idx]);
		}
	}
	return *this;
}
template <typename T>
Container<T>::Container(Container&& other) noexcept
	: m_Size{ other.m_Size }
	, m_Capacity{ other.m_Capacity }
	, m_pElements{ other.m_pElements }
{
	other.m_Capacity = 0;
	other.m_Size = 0;
	other.m_pElements = nullptr;
}
template <typename T>
Container<T>& Container<T>::operator=(Container<T>&& other)noexcept
{
	if (this != &other)// no self assignment
	{
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		delete[] m_pElements;
		m_pElements = other.m_pElements;

		other.m_Size = 0;
		other.m_pElements = nullptr;
		other.m_Capacity = 0;
	}
	return *this;
}
template <typename T>
Container<T>::~Container()
{
	delete[] m_pElements;
	m_pElements = nullptr;
}
template <typename T>
int Container<T>::Size() const
{
	return m_Size;
}
template <typename T>
int Container<T>::Capacity() const
{
	return m_Capacity;
}
template <typename T>
T Container<T>::Get(int index) const
{
	assert(index >= 0 && index < m_Size);
	return m_pElements[index];
}
template <typename T>
void Container<T>::Set(int index, const T& value)
{
	assert(index >= 0 && index < m_Size);
	m_pElements[index] = value;
}
template <typename T>
void Container<T>::PushBack(const T& value)
{
	if (!(m_Size < m_Capacity))
	{
		Reserve(m_Capacity * 2);
	}
	m_pElements[m_Size] = value;
	++m_Size;
}
template <typename T>
T& Container<T>::operator[](int index)
{
	assert(index >= 0 && index < m_Size);
	return m_pElements[index];
}
template <typename T>
const T& Container<T>::operator[](int index) const
{
	assert(index >= 0 && index < m_Size);
	return m_pElements[index];
}
template <typename T>
void Container<T>::Reserve(int newCapacity)
{
	if (newCapacity <= m_Capacity)
	{
		return;
	}

	// Dynamically allocate memory
	T* pCopiedElements = new T[newCapacity] {};
	// Copy the elements into this new memory
	for (int i{ 0 }; i < m_Size; ++i)
	{
		pCopiedElements[i] = m_pElements[i];
	}
	// Free the old memory
	delete[] m_pElements;

	// Adapt the data members to this new situation
	m_pElements = pCopiedElements;
	m_Capacity = newCapacity;
}
