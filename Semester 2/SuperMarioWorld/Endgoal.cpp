#include "pch.h"
#include "Endgoal.h"
#include "Player.h"

Endgoal::Endgoal(const Point2f& pos)
	:CheckPoint(pos)
{
	m_Rect.width = 48.f;
	m_Rect.height = 144.f;
	m_Rect.bottom = -64.f;

	m_BarRect.width = 24.f;
	m_BarRect.height = 8.f;
	m_BarRect.left = 48.f;
	m_BarRect.bottom = 8.f;
	m_BarPos = Point2f{ m_Position.x + 14.f,m_Position.y + m_Rect.height * 0.5f };
}

void Endgoal::TriggerLogic(Player* player)
{
	player->Win();
}
