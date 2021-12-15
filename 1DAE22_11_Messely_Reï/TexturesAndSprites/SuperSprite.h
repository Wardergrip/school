#pragma once
class Sprite; // Class forward declaration

class SuperSprite
{
public:
	SuperSprite(int nrOfStates);
	~SuperSprite();

	void InitState(int stateIdx, const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale, bool isSingleLoop = 0);
	void ChangeStateSingleLoop(int stateIdx, bool isSingleLoop);
	void DrawSte(int stateIdx, const Point2f& pos);
	void DrawSte(int stateIdx, float x, float y);

private:
	int m_NrOfStates;
	Sprite* m_Sprites;

};

