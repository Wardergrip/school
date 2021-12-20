#pragma once
class Sprite; // Class forward declaration

class SuperSprite
{
public:
	SuperSprite(int nrOfStates);
	~SuperSprite();

	void InitState(int stateIdx, const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale, bool isSingleLoop = 0);
	void ChangeStateSingleLoop(int stateIdx, bool isSingleLoop);
	bool ChangeCurrentState(int stateIdx);

	void DrawSte(int stateIdx, const Point2f& pos);
	void DrawSte(int stateIdx, float x, float y);
	void DrawLastSte(const Point2f& pos);
	void DrawLastSte(float x, float y);

	bool UpdateSte(float elapsedSec);

	float GetFrameWidth(int stateIdx);
	float GetFrameHeight(int stateIdx);

private:
	int m_NrOfStates;
	Sprite* m_Sprites;
	int m_LastStateIdx;

	bool IsCorrectStateIdx(int stateIdx);
};

