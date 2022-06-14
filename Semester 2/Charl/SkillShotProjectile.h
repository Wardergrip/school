#pragma once

#include "Transform.h"

#include <vector>

class Unit;

class SkillShotProjectile
{
public:
	static void InitUnitVector(std::vector<Unit*>* unitVector);
protected:
	static std::vector<Unit*>* c_UnitVector;

public:
	SkillShotProjectile(const Point2f& startingPos, const Point2f& destination, float damage = 10.f, float speed = 300.f);
	SkillShotProjectile(const SkillShotProjectile& skillshotprojectile) = delete;
	SkillShotProjectile& operator=(const SkillShotProjectile& skillshotprojectile) = delete;
	SkillShotProjectile(SkillShotProjectile&& skillshotprojectile) = delete;
	SkillShotProjectile& operator=(SkillShotProjectile&& skillshotprojectile) = delete;
	~SkillShotProjectile();

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	virtual bool ReadyToDelete() const;

protected:
	Transform m_Transform;
	float m_Speed;
	float m_Damage;
	Point2f m_Destination;
	Rectf m_Hitbox;

	bool m_ReadyToDelete;
};

