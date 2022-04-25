#pragma once
#include "DaeRectangle.h"
#include "Texture.h"

class DaeRectLabel : public DaeRectangle
{
public:
	DaeRectLabel( const Point2f& center, float width, float height, const Color4f& color, const std::string& label, const Color4f& textColor, TTF_Font* pFont );
	~DaeRectLabel( );

	void Draw( ) const override;
	std::string ToString() const override;

private: 
	Texture* m_pLabelText;
	std::string m_Label;
	Color4f m_TextCol;
	float m_MarginX;
	float m_MarginY;
};

 
