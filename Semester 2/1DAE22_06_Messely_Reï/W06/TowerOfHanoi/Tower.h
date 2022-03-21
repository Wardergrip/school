#pragma once
#include <vector>
class Disk;
class Tower
{
public:
	Tower(const Point2f& pos);
	Tower(const Tower& t) = delete;
	Tower& operator=(const Tower& t) = delete;
	~Tower();

	void Draw() const;

	void Select(const Point2f& mousePos);
	void FollowMouse(const Point2f& mousePos);
	void Deselect(const Point2f& mousePos,Tower* pTowers);

	Rectf GetTowerRect();

	void Pushback(Disk* d);
	void Popback();

private:
	Point2f m_Pos;
	std::vector<Disk*> m_pDisks;
	int m_Selected;
};

