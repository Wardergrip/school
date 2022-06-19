#include "pch.h"
#include "TargetDummy.h"

#include "InfoPlate.h"

#include "Timer.h"

#include <iostream>

TargetDummy::TargetDummy(const Point2f& position)
	:Unit(position,Rectf{0,0,30,30})
	,m_pInfoPlate{new InfoPlate(this)}
	,m_pTimer{new Timer{3}}
{
	m_pInfoPlate->SetName("Target Dummy");
}

TargetDummy::~TargetDummy()
{
	delete m_pTimer;
	m_pTimer = nullptr;
}

void TargetDummy::Draw() const
{
	Unit::Draw();
	m_pInfoPlate->Draw();
}

void TargetDummy::Update(float elapsedSec)
{
	m_pTimer->Update(elapsedSec);
	if (m_pTimer->IsDone())
	{
		m_BasicStats.currentHealth = m_BasicStats.maxHealth;
	}
}

bool TargetDummy::TakeDamage(float damageAmount)
{
	m_pTimer->ResetTimer();
	std::cout << "[TARGET DUMMY] " << damageAmount << " damage taken! Health left: " << m_BasicStats.currentHealth - damageAmount << '\n';
	return Unit::TakeDamage(damageAmount);
}
