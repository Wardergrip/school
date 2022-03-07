#pragma once
#include <vector>
class GameObject;

class Game final
{
public:
	Game();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void AddEnemy();
	void AddPickUp();
	void AddWeapon();
	void ReportAll() const;
	void ReportEnemies() const;

private:
	std::vector<GameObject*> m_pGameObjects;
};
