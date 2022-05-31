#pragma once

#include "Ability.h"

class ExampleAbility final : public Ability
{
public:
	ExampleAbility(const std::string& key, const Point2f& championLocationRef);
	ExampleAbility(ExampleAbility& ability) = delete;
	ExampleAbility& operator=(ExampleAbility& ability) = delete;
	ExampleAbility(ExampleAbility&& ability) = delete;
	ExampleAbility& operator=(ExampleAbility&& ability) = delete;
	virtual ~ExampleAbility();

	void Draw() const override;

	void OnPress(const Point2f& mousePos) override;
	void OnHolding(float elapsedSec, const Point2f& mousePos) override;
	void OnRelease(const Point2f& mousePos) override;

private:
	const Point2f& m_ChampionLocationRef;
	Point2f m_LastMousePos;

	bool m_IsHoldingDown;

	void DrawIcon() const override;

};

