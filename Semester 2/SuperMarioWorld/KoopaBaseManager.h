#pragma once
#include <vector>
class Koopa;
class Shell;
class Player;
class KoopaBaseManager final
{
public:
	KoopaBaseManager();
	KoopaBaseManager(const KoopaBaseManager& k) = delete;
	KoopaBaseManager& operator=(const KoopaBaseManager& k) = delete;
	KoopaBaseManager(KoopaBaseManager&& k) = delete;
	KoopaBaseManager& operator=(KoopaBaseManager&& k) = delete;
	~KoopaBaseManager();

	void Draw() const;
	void Update(float elapsedSec, Player* player);

	void Push_back(Shell* shell, const Point2f& pos = {});
	void Push_back(Koopa* koopa, const Point2f& pos = {});

	void PushKoopaBases();

private:
	std::vector<Shell*> m_pShells;
	std::vector<Koopa*> m_pKoopas;
};

