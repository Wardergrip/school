#pragma once

class Level;
class Mario;

class Player final
{
public:
	explicit Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	~Player();

	void Draw() const;
	void Update(float elapsedSec, Level& level);

	void AddScore( unsigned int score );
	void AddLife();
	void AddCoin();
	void AddBigCoin();
	// Returns false if there are no lives left
	bool ReduceLive();

	unsigned int GetScore() const;
	int GetLives() const;
	int GetCoinAmount() const;

	Mario* GetpMario() const;
	Rectf GetMarioRect() const;
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	void DebugPrintAllStats() const;

private:
	Mario* m_pMario;

	unsigned int m_Score;
	int m_Lives;
	int m_CoinAmount;
	int m_BigCoinAmount;
};

