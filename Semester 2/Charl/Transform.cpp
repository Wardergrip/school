#include "pch.h"
#include "Transform.h"

Transform::Transform()
	:Transform(Point2f{},Vector2f{1,1},0)
{
}

Transform::Transform(const Point2f& location)
	:Transform(location,Vector2f{1,1})
{
}

Transform::Transform(const Point2f& location, const Vector2f& scale, float angle)
	:location{location}
	,scale{scale}
	,angle{angle}
{
}

void Transform::Push() const
{
	glPushMatrix();
}

void Transform::Apply(bool inverseConvention) const
{
	if (inverseConvention)
	{
		glScalef(scale.x,scale.y,1);
		glRotatef(angle,0,0,1);
		glTranslatef(location.x,location.y,0);
	}
	else
	{
		glTranslatef(location.x,location.y,0);
		glRotatef(angle,0,0,1);
		glScalef(scale.x,scale.y,1);
	}
}

void Transform::Pop() const
{
	glPopMatrix();
}

void Transform::FlipX()
{
	scale.x = -scale.x;
}

void Transform::FlipY()
{
	scale.y = -scale.y;
}
