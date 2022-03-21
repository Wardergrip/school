#pragma once
class Disk
{
public:
	enum class Size{small, medium, large};
	Disk(Disk::Size size);

	void Draw() const;

	void SetPos(const Point2f& pos);

	Disk::Size GetSize() const;
	Rectf GetRect() const;

private:
	Disk::Size m_Size;
	Rectf m_Rect;
};

