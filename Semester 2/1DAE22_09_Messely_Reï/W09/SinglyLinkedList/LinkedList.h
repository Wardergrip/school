#pragma once
#include <iostream>

struct Node final
{
	Node(int value, Node *pNext = nullptr);

	Node* pNext;
	int value;
};

class LinkedList final
{
public:
	LinkedList( );
	~LinkedList( );
	LinkedList( const LinkedList& other ) = delete;
	LinkedList& operator=( const LinkedList& other ) = delete;
	LinkedList(LinkedList&& other)noexcept = delete;
	LinkedList& operator=(LinkedList&& other)noexcept = delete;

	void PushFront( int  value );
	void PopFront( );
	void Remove( int value );
	void InsertAfter( Node* pBefore, int value );
	size_t Size( ) const;
	Node* Begin( ) const;

private: 
	Node* m_pFirstNode;
	size_t m_Size;

	// Your helper functions
};

std::ostream& operator<<( std::ostream& out, const LinkedList& list );
