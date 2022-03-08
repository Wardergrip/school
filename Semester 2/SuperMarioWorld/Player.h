#pragma once
class Player final
{
public:
	Player();

	void AddScore( unsigned int score );
	void AddLife();
	void AddCoin();
	void AddBigCoin();
	// Returns false if there are no lives left
	bool ReduceLive();

	unsigned int GetScore() const;
	int GetLives() const;
	int GetCoinAmount() const;

	void DebugPrintAll() const;

private:
	unsigned int m_Score;
	int m_Lives;
	int m_CoinAmount;
	int m_BigCoinAmount;
};

