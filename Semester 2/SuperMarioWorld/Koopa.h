#pragma once
#include "KoopaBase.h"
class Shell;
class Koopa final : public KoopaBase
{
public:
	Koopa();

private:
	Shell* m_pShell;
};

