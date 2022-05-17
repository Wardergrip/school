#pragma once
#include <vector>
class PickUp;
class Player;
class PickUpManager final
{
public:
	PickUpManager();
	PickUpManager(const PickUpManager& p) = delete;
	PickUpManager& operator=(const PickUpManager& p) = delete;
	PickUpManager(PickUpManager&& p) = delete;
	PickUpManager& operator=(PickUpManager&& p) = delete;
	~PickUpManager();

	void Draw() const;

	void Update(float elapsedSec, Player* player);
	void Push_back(PickUp* pickup);

	void PushPickUps();
private:
	std::vector<PickUp*> m_pPickUps;
};

