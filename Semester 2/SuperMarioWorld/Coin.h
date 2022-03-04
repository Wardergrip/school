#pragma once
#include "PickUp.h"
class Coin final : public PickUp
{
public:
	enum class Type {normal, big};
	Coin(Type type, const Point2f& spawnPos = {});
	virtual ~Coin();
	
	virtual void UpdateAnim(float elapsedSec) override;
private:
	static Texture* m_NormalCoinTexture;
	static Texture* m_BigCoinTexture;
	static int m_Instances;

	bool m_AnimGoingUp;
};

