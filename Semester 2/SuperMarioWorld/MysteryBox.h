#pragma once
#include "GameObject.h"
class Texture;
class PickUp;
class MysteryBox final : public GameObject
{
public:
	explicit MysteryBox(const Point2f& pos = {}, PickUp* pPickUp = nullptr);
	MysteryBox(MysteryBox& m) = delete;
	MysteryBox& operator=(MysteryBox& m) = delete;
	MysteryBox(MysteryBox&& m) = delete;
	MysteryBox& operator=(MysteryBox&& m) = delete;
	~MysteryBox();

	void Draw() const;
	void Update(float elapsedSec);

	Rectf GetRect() const;
	Rectf GetBottomHitbox() const;
	bool IsWantingToGivePickUp() const;
	bool IsOverlapping(const Rectf& other) const;
	bool IsOverlappingBottomHitbox(const Rectf& other) const;

	PickUp* GivePickUp();
	PickUp* GetPickUp() const;

	void Bump();
private:
	static int m_Instances;
	static Texture* m_pTexture;
	static const int m_FramesPerSec;

	float m_AccuSec;
	int m_CurrentFrame;

	bool m_WantsToGive;
	bool m_IsBumped;
	float m_BumpedAccuSec;
	float m_PrebumpedYPos;

	PickUp* m_pPickUp;

	Point2f m_Position;

	void UpdateAnim(float elapsedSec);
};

