#include "pch.h"
#include "Level.h"
#include "utils.h"
using namespace utils;

Level::Level()
	:m_Vertices{}
{
}

Level::~Level()
{
	m_Vertices.clear();
}

void Level::DebugDraw(const Color4f& col) const
{
	SetColor(col);
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if ((i + 1) < m_Vertices.size())
		{
			DrawLine(m_Vertices[i], m_Vertices[i + 1]);
		}
	}
}

void Level::Push_back(const Point2f& p)
{
	m_Vertices.push_back(p);
}

bool Level::IsOnTop(const Rectf& other) const
{
	HitInfo HI{};
	return Raycast(m_Vertices, Point2f{ other.left + other.width / 2,other.bottom - 1}, Point2f{ other.left + other.width / 2,other.bottom + other.height / 2 }, HI);
}

bool Level::IsColliding(const Rectf& other) const
{
	HitInfo HI{};
	return Raycast(m_Vertices, Point2f{ other.left + other.width / 2,other.bottom }, Point2f{ other.left + other.width / 2,other.bottom + other.height / 2 }, HI);
}
