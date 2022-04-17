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

void Platform::DebugDraw(const Color4f& col, float lineThickness) const
{
	SetColor(col);
	for (size_t i{ 0 }; i < m_Vertices.size(); ++i)
	{
		if ((i + 1) < m_Vertices.size())
		{
			DrawLine(m_Vertices[i], m_Vertices[i + 1], lineThickness);
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

bool Platform::IsFullyOnTop(const Rectf& other)
{
	HitInfo HI{};
	float offSet{ 1 };
	bool firstCheck{ false };
	if (Raycast(m_Vertices, Point2f{ other.left,other.bottom + other.height / 2 }, Point2f{ other.left,other.bottom - offSet }, HI))
	{
		firstCheck = true;
	}
	if (Raycast(m_Vertices, Point2f{ other.left + other.width,other.bottom + other.height / 2 }, Point2f{ other.left + other.width,other.bottom - offSet }, HI))
	{
		return firstCheck;
	}
	return false;
}

bool Platform::IsHorizontallyTouching(const Rectf& other, HitInfo& hi, const Vector2f& velocity, float horDirection) const
{
	HitInfo HI{};
	const float velX{ std::abs(velocity.x) };
	// This offset is to make sure that clipping vertically isn't seen as a touch
	float offsetBL{ 1 };
	// Sprinting = longer raycast (further out of charachter)
	float sidewaysOffset{ velX / 50.0f };
	if (sidewaysOffset < 1) sidewaysOffset = 1;
	// Raycast points
	Point2f leftTop{ other.left - sidewaysOffset,other.bottom + other.height };
	Point2f rightTop{ other.left + other.width + sidewaysOffset,other.bottom + other.height };
	Point2f leftBot{ other.left - sidewaysOffset,other.bottom + offsetBL };
	Point2f rightBot{ other.left + other.width + sidewaysOffset,other.bottom + offsetBL };

	if (horDirection >= 0.5f)
	{
		leftTop.x += other.width / 2;
		leftBot.x += other.width / 2;
	}
	else if (horDirection <= -0.5f)
	{
		rightTop.x -= other.width / 2;
		rightBot.x -= other.width / 2;
	}

	if (Raycast(m_Vertices, leftBot, rightBot, HI))
	{
		hi = HI;
		return true;
	}
	else if (Raycast(m_Vertices, leftTop, rightTop, HI))
	{
		hi = HI;
		return true;
	}
	return false;
}
