#pragma once
#include "Vector2f.h"
class GameObject
{
public:
    explicit GameObject(const Point2f& center, float width,float height);
    explicit GameObject(const Rectf& rect);
    explicit GameObject();
    GameObject(const GameObject& g) = delete;
    GameObject& operator=(const GameObject& g) = delete;
    virtual ~GameObject();

    static const float m_Scale;

protected:
    const static Vector2f m_Gravity;

    Rectf m_Rect;

    Point2f GetCenter() const;
    void SetCenter(const Point2f& center);
};