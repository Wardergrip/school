#pragma once
class Player
{
public:
	Player();

	void AddScore( unsigned int score );
	void AddLive();
	void AddCoin();
	// Returns false if there are no lives left
	bool ReduceLive();

	unsigned int GetScore() const;
	int GetLives() const;
	int GetCoinAmount() const;

private:
	unsigned int m_Score;
	int m_Lives;
	int m_CoinAmount;
};

