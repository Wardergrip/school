#include "pch.h"
#include "ProjectileManager.h"

#include "LockOnProjectile.h"

#include "Champion.h"

ProjectileManager::ProjectileManager(int reserveLockOn)
    :m_pLockOnProjs{ reserveLockOn }
    ,m_LastMousePos{0,0}
    ,m_LastShooter{ nullptr }
    ,m_LastUnits{ nullptr }
{
}

ProjectileManager::~ProjectileManager()
{
    for (size_t i{ 0 }; i < m_pLockOnProjs.size(); ++i)
    {
        delete m_pLockOnProjs[i];
        m_pLockOnProjs[i] = nullptr;
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

void ProjectileManager::PushBack(const Point2f& startingPos, Unit* target, float damage, float speed)
{
    PushBack(new LockOnProjectile(startingPos, target, damage, speed));
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

void ProjectileManager::DrawAll() const
{
    for (LockOnProjectile* proj : m_pLockOnProjs)
    {
        if (proj)
        {
            proj->Draw();
        }
    }
}

void ProjectileManager::UpdateAll(float elapsedSec)
{
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
    TryAutoAttack(m_LastMousePos, m_LastShooter, m_LastUnits);
}

void ProjectileManager::TryAutoAttack(const Point2f& mousePos, Champion* shooter, std::vector<Unit*>* units)
{
    if ((shooter == nullptr) || (units == nullptr))
    {
        return;
    }

    for (size_t i{ 0 }; i < units->size(); ++i)
    {
        if (units->at(i)->IsOverlapping(mousePos))
        {
            float distance{ Vector2f{ shooter->GetTransform().location - units->at(i)->GetTransform().location }.Length() };
            if (shooter->GetAutoAttackRangeRadius() < distance)
            {
                break;
            }
            if (shooter->IsAAReadyAndReset())
            {
                PushBack(shooter->GetTransform().location, units->at(i));
            }
            shooter->StopMovement();
            shooter->RotateTowards(mousePos);
            break;
        }
    }
    if (&mousePos != &m_LastMousePos)
    {
        m_LastMousePos = mousePos;
    }
    if (units != m_LastUnits)
    {
        m_LastUnits = units;
    }
    if (shooter != m_LastShooter)
    {
        m_LastShooter = shooter;
    }
}
