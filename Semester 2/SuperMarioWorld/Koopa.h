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

	void Draw() const override;
	void Update(float elapsedSec, const Player& player) override;

	void AboutToDie();
	void ForceDie();

	Shell* GetShell() const;
	bool IsDead() const;
	bool IsWantingToGiveShell() const;
	Shell* GiveShell();
	void SetShell(Shell* pShell);

private:
	Shell* m_pShell;
	bool m_IsDead;
	bool m_IsHurt;
	bool m_IsGivingShell;

	// Anim stuff
	static int m_FramesPerSec;

	float m_AnimTime;
	int m_CurrentFrame;

	void UpdateAnim(float elapsedSec);
};

