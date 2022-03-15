#pragma once
class Texture;

class HUD
{
public:
	HUD(const Point2f& topLeft, int totalPowerUps);
	~HUD();

	void Draw() const;

	void PowerUpHit();

private:
	Point2f m_BottomLeft;
	int m_TotalPowerUps;
	int m_HitPowerUps;

	Texture* m_pLeftTexture;
	Texture* m_pRightTexture;
	Texture* m_pPowerUpTexture;
};

