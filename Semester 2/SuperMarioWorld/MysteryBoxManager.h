#pragma once
#include <vector>
class MysteryBox;
class Player;
class PickUpManager;
class MysteryBoxManager final
{
public:
	MysteryBoxManager();
	MysteryBoxManager(const MysteryBoxManager& m) = delete;
	MysteryBoxManager& operator=(const MysteryBoxManager& m) = delete;
	MysteryBoxManager(MysteryBoxManager&& m) = delete;
	MysteryBoxManager& operator=(MysteryBoxManager&& m) = delete;
	~MysteryBoxManager();

	void Draw() const;
	void Update(float elapsedSec, Player* player, PickUpManager* pickupmanager);
	void Push_back(MysteryBox* m);
private:
	std::vector<MysteryBox*> m_pMysteryBoxes;
};

