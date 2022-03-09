#include "pch.h"
#include "GameObject.h"

const float GameObject::m_Scale{ 1.75f };
const Vector2f GameObject::m_Gravity{ 0,-2600};

GameObject::GameObject(const Point2f& center, float width,float height)
    :m_Rect{center.x - width / 2,center.y - height / 2,width,height}
{
}

GameObject::GameObject(const Rectf& rect)
{
    m_Rect = rect;
}

GameObject::GameObject()
    :GameObject(Point2f{},0,0)
{
}

GameObject::~GameObject()
{
}

Point2f GameObject::GetCenter() const
{
    return Point2f{m_Rect.left + m_Rect.width / 2,m_Rect.bottom + m_Rect.height / 2};
}

void GameObject::SetCenter(const Point2f& center)
{
    m_Rect.left = center.x - m_Rect.width;
    m_Rect.bottom = center.y - m_Rect.height;
}