#include "pch.h"
#include "ProjectileManager.h"

#include "LockOnProjectile.h"

ProjectileManager::ProjectileManager(int reserveLockOn)
    :m_pLockOnProjs{ reserveLockOn }
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
}
