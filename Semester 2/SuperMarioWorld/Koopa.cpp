#include "pch.h"
#include "Koopa.h"
#include "Shell.h"

Koopa::Koopa(Color color)
	:KoopaBase(color,Type::shelled)
	,m_pShell{new Shell(color)}
{
}

Koopa::~Koopa()
{
	if (m_pShell != nullptr)
	{
		delete m_pShell;
		m_pShell = nullptr;
	}
}

Shell* Koopa::GiveShell()
{
	Shell* pS{ m_pShell };
	delete m_pShell;
	m_pShell = nullptr;
	return pS;
}

Shell* Koopa::GetShell() const
{
	return m_pShell;
}
