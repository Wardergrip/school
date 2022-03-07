#pragma once
#include "DaeShape.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle( const Point2f& center, float width, float height, const Color4f& color );

	void Draw( ) const override;
};

 
