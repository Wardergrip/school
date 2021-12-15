#pragma once
#include "utils.h"

class Sprite
{
public:
	Sprite(const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale = 1, bool loopOnce = false);
	Sprite(const std::string& filename);
	Sprite();
	~Sprite();

	bool ChangeTexture(const std::string& filename, int nrCols, int nrRows, int nrOfFrames, float frameSec, float scale = 1, bool loopOnce = false);
	bool Update(float elapsedSec);
	void InitLoopOnce();
	void ChangeLoopOnce(bool loopOnce);
	void Draw(const Point2f& pos);
	float GetFrameWidth();
	float GetFrameHeight();

private:
	utils::Texture m_Texture;
	int m_Cols;
	int m_Rows;
	int m_NrOfFrames;
	float m_FrameSec;
	float m_AccuSec;
	int m_ActFrame;
	float m_Scale;
	bool m_LoopOnce;
};

