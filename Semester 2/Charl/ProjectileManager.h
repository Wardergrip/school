#pragma once

#include <vector>

class LockOnProjectile;
class Unit;
class Champion;

class ProjectileManager final
{
public:
	ProjectileManager(int reserveLockOn = 20);
	ProjectileManager(const ProjectileManager& projMan) = delete;
	ProjectileManager& operator=(const ProjectileManager& projMan) = delete;
	ProjectileManager(ProjectileManager&& projMan) = delete;
	ProjectileManager& operator=(ProjectileManager&& projMan) = delete;
	~ProjectileManager();

	LockOnProjectile* operator[](size_t idx);
	LockOnProjectile* operator[](int idx);
	const LockOnProjectile* operator[](size_t idx) const;
	const LockOnProjectile* operator[](int idx) const;

	void PushBack(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	void PushBack(LockOnProjectile* proj);

	void DrawAll() const;
	void UpdateAll(float elapsedSec);

	void TryAutoAttack(const Point2f& mousePos, Champion* shooter, std::vector<Unit*>* units);

private:
	std::vector<LockOnProjectile*> m_pLockOnProjs;
	Point2f m_LastMousePos;
	Champion* m_LastShooter;
	std::vector<Unit*>* m_LastUnits;
};

