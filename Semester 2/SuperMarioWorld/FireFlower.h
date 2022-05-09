#pragma once
#include "PickUp.h"
class FireFlower final : public PickUp
{
public:
	explicit FireFlower(const Point2f& pos = {});
	FireFlower(const FireFlower& f) = delete;
	FireFlower& operator=(const FireFlower&) = delete;
	FireFlower(FireFlower&& f) = delete;
	FireFlower& operator=(FireFlower&& f) = delete;
	~FireFlower() = default;
};

