#pragma once
#include "Vector2f.h"
class GameObject
{
public:
    GameObject(const Point2f& center, float width,float height);
    GameObject(const Rectf& rect);
    GameObject();
    virtual ~GameObject();

    static const float m_Scale;

protected:
    const static Vector2f m_Gravity;

    Rectf m_Rect;

    Point2f GetCenter() const;
    void SetCenter(const Point2f& center);
};