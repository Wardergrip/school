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

bool Level::IsOnTop(Rectf& other)
{
	HitInfo HI{};
	// How deep does the ray go under the shape
	float offSet{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + other.height / 2 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		// Following line may induce jitters
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + other.height / 2 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	return false;
}

bool Level::IsHorizontallyTouching(const Rectf& other) const
{
	HitInfo HI{};
	// This offset is to make sure that clipping vertically isn't seen as a touch
	float offsetBL{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left - 1,other.bottom + offsetBL}, Point2f{ other.left + other.width + 1,other.bottom + offsetBL}, HI))
	{
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left - 1,other.bottom + other.height }, Point2f{ other.left + other.width + 1,other.bottom + other.height }, HI))
	{
		return true;
	}
	return false;
}
