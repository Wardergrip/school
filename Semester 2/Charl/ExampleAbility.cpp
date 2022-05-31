#include "pch.h"
#include "ExampleAbility.h"

#include <iostream>
#include "utils.h"

ExampleAbility::ExampleAbility(const std::string& key, const Point2f& championLocationRef)
	:Ability(Type::skillshot,key,"ExampleAbility",3)
	,m_ChampionLocationRef{championLocationRef}
	,m_IsHoldingDown{false}
	,m_LastMousePos{}
{
}

ExampleAbility::~ExampleAbility()
{
}

void ExampleAbility::Draw() const
{
	if (m_IsHoldingDown)
	{
		utils::DrawLine(m_ChampionLocationRef, m_LastMousePos);
	}
}

void ExampleAbility::OnPress(const Point2f& mousePos)
{
	if (m_IsHoldingDown) return;
	else m_IsHoldingDown = true;
	std::cout << "[EXAMPLEABILITY] OnPress\n";
}

void ExampleAbility::OnHolding(float elapsedSec, const Point2f& mousePos)
{
	std::cout << "[EXAMPLEABILITY] OnHold\n";
	m_LastMousePos = mousePos;
}

void ExampleAbility::OnRelease(const Point2f& mousePos)
{
	m_IsHoldingDown = false;
	std::cout << "[EXAMPLEABILITY] OnRelease\n";
}

void ExampleAbility::DrawIcon() const
{
	
}
