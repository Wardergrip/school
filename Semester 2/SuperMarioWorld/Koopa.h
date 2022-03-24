#pragma once
#include "KoopaBase.h"
class Shell;
class Koopa final : public KoopaBase
{
public:
	explicit Koopa(Color color = Color::green);
	Koopa(const Koopa& k) = delete;
	Koopa& operator=(const Koopa& k) = delete;
	Koopa(Koopa&& k) = delete;
	Koopa& operator=(Koopa&& k) = delete;
	~Koopa();

	//void Update(float elapsedSec, const Player& player) override;

	Shell* GetShell() const;
	Shell* GiveShell();

private:
	Shell* m_pShell;
};

