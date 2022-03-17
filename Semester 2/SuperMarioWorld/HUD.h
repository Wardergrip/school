#pragma once
class Player;

class HUD final
{
public:
	explicit HUD();
	HUD(const HUD& h) = delete;
	HUD& operator=(const HUD& h) = delete;
	~HUD() = default;

private:
	const Player& m_PlayerRef;
};

