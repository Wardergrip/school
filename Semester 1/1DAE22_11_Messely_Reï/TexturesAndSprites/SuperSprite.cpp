#include "pch.h"
#include "SuperSprite.h"
#include "Sprite.h"
#include <iostream>
using namespace utils;

SuperSprite::SuperSprite(int nrOfStates)
	:m_NrOfStates{nrOfStates}
	,m_Sprites{nullptr}
	,m_LastStateIdx{0}
{
	m_Sprites = new Sprite[m_NrOfStates]{};
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
	if (IsCorrectStateIdx(stateIdx))
	{
		m_Sprites[stateIdx].ChangeLoopOnce(isSingleLoop);
	}
	else
	{
		std::cout << "ChangeStateSingleLoop Error: stateIdx (" << stateIdx << ") is out of bounds. There are only " << m_NrOfStates << " amount of states.\n";
	}
}

// Changes the state of the SuperSprite.
bool SuperSprite::ChangeCurrentState(int stateIdx)
{
	if (IsCorrectStateIdx(stateIdx))
	{
		m_LastStateIdx = stateIdx;
		return true;
	}
	return false;
}

// Draws the SuperSprite in the requested state at the requested pos. 
void SuperSprite::DrawSte(int stateIdx, const Point2f& pos)
{
	m_LastStateIdx = stateIdx;
	m_Sprites[m_LastStateIdx].Draw(pos);
}
// Draws the SuperSprite in the requested state at the requested pos. 
void SuperSprite::DrawSte(int stateIdx, float x, float y)
{
	DrawSte(stateIdx, Point2f{ x,y });
}
// Draws the SuperSprite in the last drawn state at the requested pos. 
void SuperSprite::DrawLastSte(const Point2f& pos)
{
	DrawSte(m_LastStateIdx, pos);
}
// Draws the SuperSprite in the last drawn state at the requested pos. 
void SuperSprite::DrawLastSte(float x, float y)
{
	DrawSte(m_LastStateIdx, Point2f{x,y});
}

// Updates the sprite so it moves forward in the tilesheet.
bool SuperSprite::UpdateSte(float elapsedSec)
{
	return (m_Sprites[m_LastStateIdx].Update(elapsedSec));
}


// Gives the width of the scaled frame
float SuperSprite::GetFrameWidth(int stateIdx)
{
	if (IsCorrectStateIdx(stateIdx))
	{
		return (m_Sprites[stateIdx].GetFrameWidth());
	}
	return 0.0f;
}
// Gives the height of the scaled frame
float SuperSprite::GetFrameHeight(int stateIdx)
{
	if (IsCorrectStateIdx(stateIdx))
	{
		return (m_Sprites[stateIdx].GetFrameHeight());
	}
	return 0.0f;
}


// Checks if the given stateIdx is an actual possible idx of the Sprites array.
bool SuperSprite::IsCorrectStateIdx(int stateIdx)
{
	if ((stateIdx < m_NrOfStates) && (stateIdx >= 0))
	{
		return true;
	}
	return false;
}
