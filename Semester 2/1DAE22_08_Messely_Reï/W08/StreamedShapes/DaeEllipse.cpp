#include "pch.h"		
#include "DaeEllipse.h"
#include "utils.h"

DaeEllipse::DaeEllipse( const Point2f& center, float width, float height, const Color4f& color, bool isFilled )
:DaeShape{center,width,height,color}
,m_IsFilled{ isFilled }
{
}

void DaeEllipse::Draw( ) const
{
	utils::SetColor( m_Color );
	if ( m_IsFilled )
	{
		utils::FillEllipse( m_Center, m_Width / 2, m_Height / 2 );
	}
	else
	{
		utils::DrawEllipse( m_Center, m_Width / 2, m_Height / 2 );
	}
}

std::string DaeEllipse::ToString() const
{
	std::string output;
	std::string helper{ '\"' };

	output += "<DaeEllipse\n";
	output += PropertiesToString();
	output += "IsFilled=" + helper + (m_IsFilled ? "true" : "false") + helper + '\n';
	output += "/>\n\n";

	return output;
}
