#pragma once

class Level;
class Mario;

class Player final
{
public:
	explicit Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	Player(Player&& p) = delete;
	Player& operator=(Player&& p) = delete;
	~Player();

	void Draw() const;
	void Update(float elapsedSec, Level& level);

	void ResetAll();
	void SoftReset();

	void AddScore( unsigned int score );
	void AddLife();
	void AddCoin();
	void AddBigCoin();
	// Returns false if there are no lives left
	bool ReduceLive();

	unsigned int GetScore() const;
	int GetLives() const;
	int GetCoinAmount() const;
	unsigned int GetTime() const;
	bool IsGameOver() const;
	bool IsSoftReset() const;

	Mario* GetpMario() const;
	Rectf GetMarioRect() const;
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	void DebugPrintAllStats() const;

	void SetLastCheckPointPos(const Point2f& pos);
	Point2f GetLastCheckPointPos() const;

	void Win();

private:
	Mario* m_pMario;

	Point2f m_LastCheckPointPos;

	unsigned int m_Time;
	float m_Increment;

	unsigned int m_Score;
	int m_Lives;
	int m_CoinAmount;
	int m_BigCoinAmount;

	bool m_GameOver;
	bool m_SoftReset;

	std::string ToXML() const;
};

