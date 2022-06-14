#pragma once
#include "LockOnProjectile.h"
class AutoAttack final : public LockOnProjectile
{
public:
	AutoAttack(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	AutoAttack(const AutoAttack& autoAttack) = delete;
	AutoAttack& operator=(const AutoAttack& autoAttack) = delete;
	AutoAttack(AutoAttack&& autoAttack) = delete;
	AutoAttack& operator=(AutoAttack&& autoAttack) = delete;
	~AutoAttack();

private:
};

