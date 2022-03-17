#pragma once
#include "PickUp.h"
class Coin final : public PickUp
{
public:
	explicit Coin(Type type, const Point2f& spawnPos = {});
	Coin(const Coin& c) = delete;
	Coin& operator=(const Coin& c) = delete;
	virtual ~Coin();
	
	virtual void UpdateAnim(float elapsedSec) override;
private:
	static Texture* m_NormalCoinTexture;
	static Texture* m_BigCoinTexture;
	static int m_Instances;

	bool m_AnimGoingUp;
};

