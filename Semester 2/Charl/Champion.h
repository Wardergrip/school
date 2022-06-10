#pragma once
#include "Unit.h"

#include "AbilityInterface.h"

class InfoPlate;
class Timer;

class Champion : public Unit
{
public:
	Champion(const Window& window);
	Champion(const Champion& champ) = delete;
	Champion& operator=(const Champion& champ) = delete;
	Champion(Champion&& champ) = delete;
	Champion& operator=(Champion&& champ) = delete;
	virtual ~Champion();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e) override;
	virtual void OnMouseUp(const SDL_MouseButtonEvent& e) override;
	virtual void OnMouseMotion(const SDL_MouseMotionEvent& e) override;

	virtual void OnKeyDown(const SDL_KeyboardEvent& e, const Point2f& mousePos) override;
	virtual void OnKeyHold(float elapsedSec, const Uint8* pStates, const Point2f& mousePos) override;
	virtual void OnKeyUp(const SDL_KeyboardEvent& e, const Point2f& mousePos) override;

	bool IsAutoAttackReady() const;
	// Only resets if it returns true
	bool IsAAReadyAndReset();

	float GetAutoAttackRangeRadius() const;

protected:
	AbilityInterface* m_pAbilityInterface;
	InfoPlate* m_pInfoPlate;
	Timer* m_pAutoAttackTimer;
	float m_AutoAttackRangeRadius;
	bool m_DrawAARange;

	AbilityKey GetAppropriateAbilityKey(const SDL_KeyboardEvent& e) const;
};

