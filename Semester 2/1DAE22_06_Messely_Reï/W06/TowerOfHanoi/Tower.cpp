#include "pch.h"
#include "Tower.h"
#include "Disk.h"
#include "utils.h"
#include <iostream>
using namespace utils;

Tower::Tower(const Point2f& pos)
	:m_Pos{pos}
	,m_Selected{-1}
{
}

Tower::~Tower()
{
	for (Disk* t : m_pDisks)
	{
		delete t;
		t = nullptr;
	}
	m_pDisks.clear();
}

void Tower::Draw() const
{
	SetColor(Color4f{ 1,1,1,1 });
	FillRect(Rectf{ m_Pos.x,m_Pos.y,300,20 });
	FillRect(Rectf{ m_Pos.x + 120, m_Pos.y,30,200 });

	for (Disk* d : m_pDisks)
	{
		d->Draw();
	}
}

void Tower::Select(const Point2f& mousePos)
{
	for (int i{ 0 }; i < m_pDisks.size(); ++i)
	{
		if (IsPointInRect(mousePos, m_pDisks[i]->GetRect()))
		{
			m_Selected = i;
			return;
		}
	}
	m_Selected = -1;
}

void Tower::FollowMouse(const Point2f& mousePos)
{
	if (m_Selected == -1) return;
	m_pDisks[m_Selected]->SetPos(Point2f{ mousePos.x - m_pDisks[m_Selected]->GetRect().width / 2,mousePos.y - m_pDisks[m_Selected]->GetRect().height / 2 });
}

void Tower::Deselect(const Point2f& mousePos, Tower* pTowers)
{
	if (m_Selected == -1) return;
	else if (IsOverlapping(GetTowerRect(), m_pDisks[m_Selected]->GetRect()))
	{
		m_pDisks[m_Selected]->SetPos(Point2f{ m_Pos.x + (300 - m_pDisks[m_Selected]->GetRect().width) / 2, m_Pos.y + 20 + (m_Selected)*m_pDisks[m_Selected]->GetRect().height });
		m_Selected = -1;
		return;
	}
	for (int i{ 0 }; i < 3; ++i)
	{
		if (IsPointInRect(mousePos, pTowers[i].GetTowerRect()))
		{
			if (pTowers[i].m_pDisks.size() == 0)
			{
				pTowers[i].Pushback(m_pDisks[m_Selected]);
				this->m_pDisks.pop_back();
			}
			else if (int(pTowers[i].m_pDisks.back()->GetSize()) > int(m_pDisks[m_Selected]->GetSize()))
			{
				pTowers[i].Pushback(m_pDisks[m_Selected]);
				this->m_pDisks.pop_back();
			}
			else m_pDisks[m_Selected]->SetPos(Point2f{ m_Pos.x + (300 - m_pDisks[m_Selected]->GetRect().width) / 2, m_Pos.y + 20 + (m_Selected) * m_pDisks[m_Selected]->GetRect().height});

			m_Selected = -1;
			return;
		}
	}
}

Rectf Tower::GetTowerRect()
{
	return Rectf(m_Pos.x,m_Pos.y,300,200);
}

void Tower::Pushback(Disk* d)
{
	m_pDisks.push_back(d);
	m_pDisks[m_pDisks.size() - 1]->SetPos(Point2f{m_Pos.x + (300 - d->GetRect().width) / 2, m_Pos.y + 20 + (m_pDisks.size() - 1) * d->GetRect().height});
}

void Tower::Popback()
{
	m_pDisks.pop_back();
}

