#pragma once

#include "Transform.h"

class Unit;

class LockOnProjectile final
{
public:
	LockOnProjectile(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	LockOnProjectile(const LockOnProjectile& proj) = delete;
	LockOnProjectile& operator=(const LockOnProjectile& proj) = delete;
	LockOnProjectile(LockOnProjectile&& proj) = delete;
	LockOnProjectile& operator=(LockOnProjectile&& proj) = delete;
	~LockOnProjectile();

	void Draw() const;
	void Update(float elapsedSec);

	bool HasHit() const;

private:
	Transform m_Transform;
	float m_Speed;
	float m_Damage;
	Unit* m_pTarget;
	Rectf m_Hitbox;

	bool m_HasHit;
};

