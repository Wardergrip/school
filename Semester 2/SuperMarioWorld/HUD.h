#pragma once
class Player;
class Texture;

class HUD final
{
public:
	explicit HUD(const Player& player, const Window& window);
	HUD(const HUD& h) = delete;
	HUD& operator=(const HUD& h) = delete;
	~HUD();

	void Draw() const;



private:
	void DrawChar(const Point2f& pos, char charachter, bool scaleChar = false) const;
	void DrawString(const Point2f& pos, const std::string& message, bool scaleChar = true) const;
	void DrawString(const Point2f& pos, int number, bool scaleChar = true) const;

	void DrawMario(const Point2f& pos = {}) const;
	void DrawX(const Point2f& pos = {}) const;
	void DrawCoin(const Point2f& pos = {}) const;
	void DrawLives(const Point2f& pos = {}) const;
	void DrawHolder(const Point2f& pos = {}) const;

	static const float m_Scale;
	const Player& m_PlayerRef;
	const Window& m_WindowRef;

	Texture* m_pFont;
	Texture* m_pCourseClear;
	Texture* m_pPowerUpHold;
	Texture* m_pScoreTextures;
};

