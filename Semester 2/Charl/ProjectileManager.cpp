#include "pch.h"
#include "ProjectileManager.h"

#include "AutoAttack.h"
#include "SkillShotProjectile.h"

#include "Champion.h"

// STATICS

std::vector<Unit*>* ProjectileManager::c_Units{nullptr};

std::vector<Unit*>* ProjectileManager::GetUnits()
{
    return c_Units;
}

void ProjectileManager::ChangeUnits(std::vector<Unit*>* units)
{
    c_Units = units;
}

// NON STATICS

ProjectileManager::ProjectileManager(std::vector<Unit*>* units, int reserveLockOn, int reserveSkillShot)
    :m_pLockOnProjs{ reserveLockOn }
    ,m_pSkillShotProjs{ reserveSkillShot }
    ,m_LastMousePos{0,0}
    ,m_LastShooter{ nullptr }
    ,m_IsShiftHeld{false}
{
    SkillShotProjectile::InitUnitVector(units);
}

ProjectileManager::~ProjectileManager()
{
    for (size_t i{ 0 }; i < m_pLockOnProjs.size(); ++i)
    {
        delete m_pLockOnProjs[i];
        m_pLockOnProjs[i] = nullptr;
    }
    for (size_t i{ 0 }; i < m_pSkillShotProjs.size(); ++i)
    {
        delete m_pSkillShotProjs[i];
        m_pSkillShotProjs[i] = nullptr;
    }
}

LockOnProjectile* ProjectileManager::operator[](size_t idx)
{
    return m_pLockOnProjs[idx];
}

LockOnProjectile* ProjectileManager::operator[](int idx)
{
    return m_pLockOnProjs[idx];
}

const LockOnProjectile* ProjectileManager::operator[](size_t idx) const
{
    return m_pLockOnProjs[idx];
}

const LockOnProjectile* ProjectileManager::operator[](int idx) const
{
    return m_pLockOnProjs[idx];
}

void ProjectileManager::PushBackLockOn(const Point2f& startingPos, Unit* target, float damage, float speed)
{
    PushBack(new LockOnProjectile(startingPos, target, damage, speed));
}

void ProjectileManager::PushBackAutoAttack(const Point2f& startingPos, Unit* target, float damage, float speed)
{
    PushBack(new AutoAttack(startingPos, target, damage, speed));
}

void ProjectileManager::PushBackSkillShot(const Point2f& startingPos, const Point2f& destination, float damage, float speed)
{
    PushBack(new SkillShotProjectile(startingPos, destination, damage, speed));
}

void ProjectileManager::PushBack(LockOnProjectile* proj)
{
    bool isPointerPushed{ false };
    for (size_t i{ 0 }; i < m_pLockOnProjs.size(); ++i)
    {
        if (m_pLockOnProjs[i] == nullptr)
        {
            m_pLockOnProjs[i] = proj;
            isPointerPushed = true;
            break;
        }
    }
    if (isPointerPushed == false)
    {
        m_pLockOnProjs.push_back(proj);
    }
}

void ProjectileManager::PushBack(SkillShotProjectile* proj)
{
    bool isPointerPushed{ false };
    for (size_t i{ 0 }; i < m_pSkillShotProjs.size(); ++i)
    {
        if (m_pSkillShotProjs[i] == nullptr)
        {
            m_pSkillShotProjs[i] = proj;
            isPointerPushed = true;
            break;
        }
    }
    if (isPointerPushed == false)
    {
        m_pSkillShotProjs.push_back(proj);
    }
}

void ProjectileManager::DrawAll() const
{
    for (LockOnProjectile* proj : m_pLockOnProjs)
    {
        if (proj)
        {
            proj->Draw();
        }
    }
    for (SkillShotProjectile* proj : m_pSkillShotProjs)
    {
        if (proj)
        {
            proj->Draw();
        }
    }
}

void ProjectileManager::UpdateAll(float elapsedSec, const Uint8* pStates)
{
    m_IsShiftHeld = pStates[SDL_SCANCODE_LSHIFT];

    // LOCK ON
    for (size_t i{ 0 }; i < m_pLockOnProjs.size(); ++i)
    {
        if (m_pLockOnProjs[i] == nullptr)
        {
            continue;
        }
        m_pLockOnProjs[i]->Update(elapsedSec);
        if (m_pLockOnProjs[i]->HasHit())
        {
            delete m_pLockOnProjs[i];
            m_pLockOnProjs[i] = nullptr;
        }
    }
    TryAutoAttack(m_LastMousePos, m_LastShooter);

    // SKILLSHOT
    for (size_t i{ 0 }; i < m_pSkillShotProjs.size(); ++i)
    {
        if (m_pSkillShotProjs[i] == nullptr)
        {
            continue;
        }
        m_pSkillShotProjs[i]->Update(elapsedSec);
        if (m_pSkillShotProjs[i]->ReadyToDelete())
        {
            delete m_pSkillShotProjs[i];
            m_pSkillShotProjs[i] = nullptr;
        }
    }
}

void ProjectileManager::TryAutoAttack(const Point2f& mousePos, Champion* shooter)
{
    if (shooter == nullptr)
    {
        return;
    }

    const Uint8* pStates = SDL_GetKeyboardState(nullptr);

    for (size_t i{ 0 }; i < c_Units->size(); ++i)
    {
        if (m_IsShiftHeld)
        {
            Unit* closestUnit{ shooter->GetClosestUnit(c_Units) };
            if (closestUnit == nullptr) return;
            ShooterLogic(shooter, closestUnit);
            break;
        }
        else if (c_Units->at(i)->IsOverlapping(mousePos))
        {
            ShooterLogic(shooter, c_Units->at(i));
            break;
        }
    }
    if (&mousePos != &m_LastMousePos)
    {
        m_LastMousePos = mousePos;
    }
    if (shooter != m_LastShooter)
    {
        m_LastShooter = shooter;
    }
}

void ProjectileManager::ShooterLogic(Champion* shooter, Unit* unit)
{
    float distance{ Vector2f{ shooter->GetTransform().location - unit->GetTransform().location }.Length() };
    if (shooter->GetAutoAttackRangeRadius() < distance)
    {
        return;
    }
    if (shooter->IsAAReadyAndReset())
    {
        PushBackAutoAttack(shooter->GetTransform().location, unit);
    }
    shooter->StopMovement();
    shooter->RotateTowards(unit->GetTransform().location);
}
