#include "pch.h"
#include "Platform.h"
using namespace utils;

Platform::Platform(const Rectf& rect)
	:m_Vertices{}
{
	m_Vertices.push_back(Point2f{ rect.left,rect.bottom });
	m_Vertices.push_back(Point2f{ rect.left + rect.width,rect.bottom });
	m_Vertices.push_back(Point2f{ rect.left + rect.width,rect.bottom + rect.height });
	m_Vertices.push_back(Point2f{ rect.left,rect.bottom + rect.height });
	m_Vertices.push_back(Point2f{ rect.left,rect.bottom });
}

void Platform::DebugDraw(const Color4f& col) const
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

void Platform::GetVertices(std::vector<Point2f>& output) const
{
	output = m_Vertices;
}

std::vector<Point2f> Platform::GetVertices() const
{
	return m_Vertices;
}

Platform::Platform(const Point2f& start, float length, float downwardsThickness)
	:Platform(Rectf{start.x,start.y - downwardsThickness,length,downwardsThickness})
{
}

bool Platform::IsOnTop(Rectf& other)
{
	HitInfo HI{};
	// How deep does the ray go under the shape
	float offSet{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + 1 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		// Following line may induce jitters
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + 1 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		other.bottom += offSet * (1 - HI.lambda);
		return true;
	}
	return false;
}

bool Platform::IsOnTop(const Rectf& other, HitInfo& hi)
{
	HitInfo HI{};
	float offSet{ 1 };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + other.height / 2 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		hi = HI;
		return true;
	}
	else if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + other.height / 2 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		hi = HI;
		return true;
	}
	return false;
}
