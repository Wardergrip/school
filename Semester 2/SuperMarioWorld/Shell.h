#pragma once
#include "KoopaBase.h"
#include "Koopa.h"
#include <vector>
class Shell final : public KoopaBase
{
public:
	explicit Shell(Color col = Color::green);
	Shell(const Shell& s) = delete;
	Shell& operator=(const Shell& s) = delete;
	Shell(Shell&& s) = delete;
	Shell& operator=(Shell&& s) = delete;
	~Shell() = default;

	void Kick(float horizontalDirection);
	void Throw(float horizontalDirection, const Vector2f& velocity);

	void Draw() const override;
	void Update(float elapsedSec, const Player& player) override;
	// Returns idx of the koopa hit
	int UpdateShellKoopaCollisions(std::vector<Koopa*>& pKs);
	void UpdateShellCollisions(std::vector<Shell*>& pSs);

	void SetGrabbed(bool grabbed);
	void SetUpStatus(bool status);

	bool IsGrabbed() const;
	bool IsGoingIn() const;
	float GetYPos() const;

	void SetDeathStatus(bool status);

private:
	static int m_FramesPerSec;
	static float m_KickSpeed;

	float m_AnimTime;
	int m_CurrentFrame;

	bool m_Grab;
	bool m_GoIn;
	bool m_IsDead;
	bool m_MarioUp;
};

