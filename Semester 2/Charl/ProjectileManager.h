#pragma once

#include <vector>

class LockOnProjectile;
class SkillShotProjectile;
class Unit;
class Champion;
class AutoAttack;

class ProjectileManager final
{
public:
	static std::vector<Unit*>* GetUnits();
	static void ChangeUnits(std::vector<Unit*>* units);
private:
	static std::vector<Unit*>* c_Units;
public:
	ProjectileManager(std::vector<Unit*>* units, int reserveLockOn = 30, int reserveSkillShot = 30);
	ProjectileManager(const ProjectileManager& projMan) = delete;
	ProjectileManager& operator=(const ProjectileManager& projMan) = delete;
	ProjectileManager(ProjectileManager&& projMan) = delete;
	ProjectileManager& operator=(ProjectileManager&& projMan) = delete;
	~ProjectileManager();

	LockOnProjectile* operator[](size_t idx);
	LockOnProjectile* operator[](int idx);
	const LockOnProjectile* operator[](size_t idx) const;
	const LockOnProjectile* operator[](int idx) const;

	void PushBackLockOn(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	void PushBackAutoAttack(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	void PushBackAutoAttack(AutoAttack* autoAttack);
	void PushBackSkillShot(const Point2f& startingPos, const Point2f& destination, float damage = 10.f, float speed = 300.f);
	void PushBack(LockOnProjectile* proj);
	void PushBack(SkillShotProjectile* proj);

	void DrawAll() const;
	void UpdateAll(float elapsedSec);

	void TryAutoAttack(const Point2f& mousePos, Champion* shooter, bool isNewInput = true);
	void TryAutoAttack(const Point2f& mousePos, Champion* shooter, AutoAttack* autoAttack, bool isNewInput = true);

private:
	std::vector<LockOnProjectile*> m_pLockOnProjs;
	std::vector<SkillShotProjectile*> m_pSkillShotProjs;

	Point2f m_LastMousePos;
	Champion* m_LastShooter;
	AutoAttack* m_pAutoAttackDefault;
	AutoAttack* m_LastAutoAttackUsed;

	bool m_IsShiftHeld;

	void ShooterLogic(Champion* shooter, Unit* unit);
	void ShooterLogic(Champion* shooter, Unit* unit, AutoAttack* autoAttack);
};

