#include "pch.h"
#include "Disk.h"
#include "utils.h"
using namespace utils;

Disk::Disk(Disk::Size size)
    :m_Size{size}
    ,m_Rect{0,0,0,30}
{
    m_Rect.width = int(size) * 50.f + 200;
}

void Disk::Draw() const
{
    switch (m_Size)
    {
    case Disk::Size::small:
        SetColor(Color4f{ 1,0,0,1 });
        break;
    case Disk::Size::medium:
        SetColor(Color4f{ 0,1,0,1 });
        break;
    case Disk::Size::large:
        SetColor(Color4f{ 0,0,1,1 });
        break;
    }
    FillRect(m_Rect);

    SetColor(Color4f{ 0,0,0,1 });
    DrawRect(m_Rect, 2);
}

void Disk::SetPos(const Point2f& pos)
{
    m_Rect.left = pos.x;
    m_Rect.bottom = pos.y;
}

Disk::Size Disk::GetSize() const
{
    return m_Size;
}

Rectf Disk::GetRect() const
{
    return m_Rect;
}
