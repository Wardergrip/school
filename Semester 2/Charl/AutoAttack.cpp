#include "pch.h"
#include "AutoAttack.h"

AutoAttack::AutoAttack(const Point2f& startingPos, Unit* target, float damage, float speed)
	:LockOnProjectile(startingPos,target,damage,speed)
{
}

AutoAttack::~AutoAttack()
{
}
