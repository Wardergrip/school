#pragma once
#include "CheckPoint.h"
class Endgoal final : public CheckPoint
{
public:
	Endgoal(const Point2f& pos);
	Endgoal(Endgoal& e) = delete;
	Endgoal& operator=(Endgoal& e) = delete;
	Endgoal(Endgoal&& e) = delete;
	Endgoal& operator=(Endgoal&& e) = delete;

private:
	void TriggerLogic(Player* player) override;
};

