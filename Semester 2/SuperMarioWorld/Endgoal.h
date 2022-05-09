#pragma once
#include "CheckPoint.h"
class Endgoal final : public CheckPoint
{
public:
	Endgoal(const Point2f& pos);
	Endgoal(const Endgoal& e) = delete;
	Endgoal& operator=(const Endgoal& e) = delete;
	Endgoal(Endgoal&& e) = delete;
	Endgoal& operator=(Endgoal&& e) = delete;
	~Endgoal() = default;

private:
	void TriggerLogic(Player* player) override;
};

