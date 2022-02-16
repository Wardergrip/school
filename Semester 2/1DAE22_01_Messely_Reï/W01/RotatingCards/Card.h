#pragma once
class Texture;

class Card final
{
public:
	enum class Suit
	{
		clubs = 1,
		diamonds = 2,
		hearts = 3,
		spades = 4
	};

	explicit Card( Suit suit, int rank );
	~Card();
	void Draw() const; // const member functions is new, will be explained in the theory
	void Update(float elapsedSec);

	const int m_MinRank;
	const int m_MaxRank;
	float GetWidth()const ;// const member functions is new, will be explained in the theory
	float GetHeight()const ;// const member functions is new, will be explained in the theory
	void SetAngle(float angle);

private:
	float m_Scale;
	float m_Width;
	float m_Height;
	const Texture *m_pTexture;
	const Suit m_Suit;
	const int m_Rank;

	Circlef m_Orbit;
	float m_Angle;
};