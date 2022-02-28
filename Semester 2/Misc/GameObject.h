#pragma once
#pragma region DeleteThis
struct Point2f
{
    Point2f(float X,float Y){x=X;y=Y;};
    Point2f(){x=0;y=0;};
    float x;
    float y;
};
struct Rectf
{
    Rectf(float LEFT,float BOTTOM,float WIDTH,float HEIGHT){left=LEFT;bottom=BOTTOM;width=WIDTH;height=HEIGHT;};
    Rectf(){left=0;bottom=0;width=0;height=0;};
    float left,bottom,width,height;
};
#pragma endregion DeleteThis
class GameObject
{
public:
    GameObject(const Point2f& center, float width,float height);
    GameObject(const Rectf& rect);
    GameObject();
    ~GameObject();

protected:
    Rectf m_Rect;

    Point2f GetCenter() const;
    void SetCenter(const Point2f& center);
};