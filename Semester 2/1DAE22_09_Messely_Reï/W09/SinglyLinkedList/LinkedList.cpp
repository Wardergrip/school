#include "pch.h"
#include "LinkedList.h"

Node::Node(int value, Node *pNext)
	:value{ value }
	, pNext{ pNext }
{
}

LinkedList::LinkedList()
	:m_pFirstNode{nullptr}
	,m_Size{0}
{
}

LinkedList::~LinkedList()
{
	Node* currentPointer{ m_pFirstNode }, *nextPointer{nullptr};
	while (currentPointer)
	{
		nextPointer = currentPointer->pNext;
		delete currentPointer;
		currentPointer = nextPointer;
	}
	m_pFirstNode = nullptr;
	m_Size = 0;
}

// Wrap the value in a new Node object and add it as first Node of the list
void LinkedList::PushFront( int  value )
{
	Node* n{ new Node{ value, m_pFirstNode } };
	m_pFirstNode = n;
	++m_Size;
}

// Remove and delete first Node
void LinkedList::PopFront( )
{
	if (m_pFirstNode == nullptr) return;
	Node* n{ m_pFirstNode->pNext };
	delete m_pFirstNode;
	m_pFirstNode = n;
	--m_Size;
}

// Remove all Nodes having this value
void LinkedList::Remove( int value )
{
	Node* pCurrent{ m_pFirstNode }, *pPrevious{nullptr}, *pNext{nullptr};
	while (pCurrent)
	{
		pNext = pCurrent->pNext;
		if (pCurrent->value == value)
		{
			delete pCurrent;
			pCurrent = nullptr;
			if (pPrevious) pPrevious->pNext = pNext;
			else m_pFirstNode = pNext;
			--m_Size;
		}
		if (pCurrent) pPrevious = pCurrent;
		pCurrent = pNext;
	}
}

// Wrap the value in a new Node object and insert it after the specified Node 
void LinkedList::InsertAfter( Node* pBefore, int value )
{
	Node* n{ pBefore->pNext };
	pBefore->pNext = new Node(value,n);
	++m_Size;
}

// Return pointer to first Node
Node* LinkedList::Begin( ) const
{
	return m_pFirstNode;
}

// Return number of Node objects in the list
size_t LinkedList::Size( ) const
{
	return m_Size;
}

// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<( std::ostream& out, const LinkedList& list )
{
	Node* n{ list.Begin() };
	while (n)
	{
		out << n->value;
		if (n->pNext) out << ' ';
		n = n->pNext;
	}
	return out;
}
