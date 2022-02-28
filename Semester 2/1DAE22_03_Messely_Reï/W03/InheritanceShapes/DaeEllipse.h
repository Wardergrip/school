#pragma once
#include "DaeShape.h"

class DaeEllipse  : public DaeShape
{
public:
	DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled );

	void Draw( ) const;

protected: 
	bool m_IsFilled;
};

 
