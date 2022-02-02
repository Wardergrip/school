#pragma once

class Tile 
{
public:
	Tile(const Rectf& dstRect, const std::string& textPath, int nrAnimals );
	~Tile();

	void Draw();
	void CheckActivation(const Point2f& pos);
	bool CheckHit(const Point2f& pos);
	int GetCurrentAnimal( );
	void Deactivate();
	void Randomize( );

private: 
	utils::Texture m_Texture;
	Rectf m_DstRect;
	int m_NrAnimals;
	int m_CurrentAnimal;
	bool m_IsActivated;
	bool m_IsPlayable;
};
