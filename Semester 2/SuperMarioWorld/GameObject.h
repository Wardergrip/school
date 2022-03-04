#pragma once
class GameObject
{
public:
    GameObject(const Point2f& center, float width,float height);
    GameObject(const Rectf& rect);
    GameObject();
    virtual ~GameObject();

protected:
    Rectf m_Rect;

    Point2f GetCenter() const;
    void SetCenter(const Point2f& center);
};