#include "pch.h"
#include "SuperSprite.h"
#include "Sprite.h"
#include <iostream>
using namespace utils;

SuperSprite::SuperSprite(int nrOfStates)
	:m_NrOfStates{nrOfStates}
	,m_Sprites{nullptr}
{
	Sprite* m_Sprites = new Sprite[m_NrOfStates]{};
	//for (int i{ 0 }; i < m_NrOfStates; ++i)
	//{
	//	//m_Sprites[i]. = new Sprite{};
	//}
}

SuperSprite::~SuperSprite()
{
	delete[] m_Sprites;
	m_Sprites = nullptr;
}

// Use this to initialise all your states with the needed texture and information.
void SuperSprite::InitState(int stateIdx, const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale, bool isSingleLoop)
{
	if ((stateIdx < m_NrOfStates) && (stateIdx >= 0))
	{
		m_Sprites[stateIdx].ChangeTexture(filename, nrCols, nrRows, nrOfFrames, frameSec, scale);
	}
	else
	{
		std::cout << "SuperSpriteClass Error: Initstate idx is out of bounds\n";
	}
}
// Use this to change a state to a single loop.
void SuperSprite::ChangeStateSingleLoop(int stateIdx, bool isSingleLoop)
{
	if ((stateIdx < m_NrOfStates) && (stateIdx >= 0))
	{
		m_Sprites[stateIdx].ChangeLoopOnce(isSingleLoop);
	}
	else
	{
		std::cout << "ChangeStateSingleLoop Error: stateIdx (" << stateIdx << ") is out of bounds. There are only " << m_NrOfStates << " amount of states.\n";
	}
}

void SuperSprite::DrawSte(int stateIdx, const Point2f& pos)
{
	m_Sprites[stateIdx].Draw(pos);
}
void SuperSprite::DrawSte(int stateIdx, float x, float y)
{
	DrawSte(stateIdx, Point2f{ x,y });
}