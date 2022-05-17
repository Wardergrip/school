#include "pch.h"
#include "KoopaBaseManager.h"
#include "Koopa.h"
#include "Shell.h"

#include "Player.h"
#include "Mario.h"

KoopaBaseManager::KoopaBaseManager()
	:m_pShells()
	,m_pKoopas()
{
	m_pShells.reserve(16);
	m_pKoopas.reserve(16);
	m_pShells.clear();
	m_pKoopas.clear();
}

KoopaBaseManager::~KoopaBaseManager()
{
	for (size_t i{ 0 }; i < m_pShells.size(); ++i)
	{
		delete m_pShells[i];
		m_pShells[i] = nullptr;
	}
	for (size_t i{ 0 }; i < m_pKoopas.size(); ++i)
	{
		delete m_pKoopas[i];
		m_pKoopas[i] = nullptr;
	}
}

void KoopaBaseManager::Draw() const
{
	for (Koopa* koopa : m_pKoopas)
	{
		if (koopa)
		{
			koopa->Draw();
		}
	}
	for (Shell* shell : m_pShells)
	{
		if (shell)
		{
			shell->Draw();
		}
	}
}

void KoopaBaseManager::Update(float elapsedSec, Player* player)
{
	// Update Shells
	if (player->GetpMario()->IsTryingToThrowShell())
	{
		Push_back(player->GetpMario()->GiveShell());
	}
	for (size_t loopedIdx{ 0 }; loopedIdx < m_pShells.size(); ++loopedIdx)
	{
		if (m_pShells[loopedIdx] == nullptr)
		{
			continue;
		}
		m_pShells[loopedIdx]->Update(elapsedSec, player);
		if (m_pShells[loopedIdx]->IsGrabbed())
		{
			if (player->GetpMario()->GetShell())
			{
				m_pShells[loopedIdx]->SetGrabbed(false);
				m_pShells[loopedIdx]->Kick(player->GetpMario()->GetHorDirection());
			}
			else
			{
				player->GetpMario()->SetShell(m_pShells[loopedIdx]);
				m_pShells[loopedIdx] = nullptr;
				continue;
			}
		}
		m_pShells[loopedIdx]->UpdateShellCollisions(m_pShells);
		int koopaHit{ m_pShells[loopedIdx]->UpdateShellKoopaCollisions(m_pKoopas) };
		if (koopaHit == -1)
		{
			continue;
		}
		if (m_pShells[loopedIdx]->IsGoingIn())
		{
			m_pKoopas[koopaHit]->SetShell(m_pShells[loopedIdx]);
			m_pShells[loopedIdx] = nullptr;
		}
	}
	// Update Koopas
	for (size_t i{ 0 }; i < m_pKoopas.size(); ++i)
	{
		if (m_pKoopas[i] == nullptr) continue;
		m_pKoopas[i]->Update(elapsedSec, player);
		if (m_pKoopas[i]->IsDead())
		{
			delete m_pKoopas[i];
			m_pKoopas[i] = nullptr;
		}
		else if (m_pKoopas[i]->IsWantingToGiveShell())
		{
			bool isPointerPushed{ false };
			for (size_t i{ 0 }; i < m_pShells.size(); ++i)
			{
				if (m_pShells[i] != nullptr) continue;
				if (m_pKoopas[i] == nullptr) break;
				if (m_pKoopas[i]->GetShell() == nullptr) continue;
				if (isPointerPushed) continue;
				m_pShells[i] = m_pKoopas[i]->GiveShell();
				isPointerPushed = true;
			}
			if (!isPointerPushed)
			{
				m_pShells.push_back(m_pKoopas[i]->GiveShell());
			}
		}
	}
}

void KoopaBaseManager::Push_back(Shell* shell, const Point2f& pos)
{
	bool isPointerPushed{ false };
	for (size_t i{ 0 }; i < m_pShells.size(); ++i)
	{
		if (m_pShells[i] != nullptr) continue;
		if (isPointerPushed) continue;
		m_pShells[i] = shell;
		isPointerPushed = true;
	}
	if (!isPointerPushed) m_pShells.push_back(shell);
	if ((pos.x != Point2f{}.x) && (pos.y != Point2f{}.y))
	{
		shell->SetPosition(pos);
	}
}

void KoopaBaseManager::Push_back(Koopa* koopa, const Point2f& pos)
{
	m_pKoopas.push_back(koopa);
	if ((pos.x != Point2f{}.x) && (pos.y != Point2f{}.y))
	{
		koopa->SetPosition(pos);
	}
}

void KoopaBaseManager::PushKoopaBases()
{
	using Color = KoopaBase::Color;
	using Type = KoopaBase::Type;

	// First platform
	Push_back(new Koopa(Color::red), Point2f{ 570,166 });
	Push_back(new Koopa(Color::red), Point2f{ 600,166 });
	Push_back(new Koopa(Color::red), Point2f{ 630,166 });
	Push_back(new Koopa(Color::red), Point2f{ 660,166 });
	Push_back(new Koopa(Color::red), Point2f{ 680,166 });
	Push_back(new Koopa(Color::red), Point2f{ 700,166 });
	//

	Push_back(new Shell(Color::red), Point2f{ 300,150 });

	Push_back(new Shell(Color::red), Point2f{ 2220, 87 });
	Push_back(new Koopa(Color::red, Type::naked), Point2f{ 2260,87 });
	Push_back(new Shell(Color::green), Point2f{ 3024,87 });
	Push_back(new Koopa(Color::green, Type::naked), Point2f{ 3050,87 });

	Push_back(new Koopa(Color::red), Point2f{ 3825,200 });
	Push_back(new Koopa(Color::gray), Point2f{ 5400,90 });
	Push_back(new Koopa(Color::red), Point2f{ 6230,140 });

	Push_back(new Koopa(Color::red), Point2f{ 6930,90 });
	Push_back(new Koopa(Color::red), Point2f{ 6970,90 });

	Push_back(new Koopa(Color::gray), Point2f{ 7304,90 });
}
