// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley( const Point2f& position )
	:m_Position{position}
	,m_Velocity{150,150}
	,m_IsHighest{false}
	,m_IsSleeping{false}
	,m_IsInSafeArea{true}
{
	if (m_InstanceCounter == 0) m_pSmileyTexture = new Texture("Resources/Textures/Smileys.png");
	++m_InstanceCounter;
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley( )
{
	if (m_InstanceCounter == 1)
	{
		delete m_pSmileyTexture;
		m_pSmileyTexture = nullptr;
	}
	--m_InstanceCounter;
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw( )
{
	Rectf srcRect{ 0,0,m_pSmileyTexture->GetWidth() / 4,m_pSmileyTexture->GetHeight() };
	if (m_IsSleeping) srcRect.left = 3 * srcRect.width;
	else if (m_IsHighest) srcRect.left = 0;
	else if (!m_IsInSafeArea) srcRect.left = 2 * srcRect.width;
	else srcRect.left = srcRect.width;
	m_pSmileyTexture->Draw(m_Position,srcRect);
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect )
{
	if (m_IsSleeping) return;
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
	if (m_Position.x < boundingRect.left)
	{
		m_Velocity.x = abs(m_Velocity.x);
	}
	else if (m_Position.x + (m_pSmileyTexture->GetWidth() / 3) > boundingRect.left + boundingRect.width)
	{
		m_Velocity.x = -abs(m_Velocity.x);
	}
	if (m_Position.y < boundingRect.bottom)
	{
		m_Velocity.y = abs(m_Velocity.y);
	} 
	else if (m_Position.y + m_pSmileyTexture->GetHeight() > boundingRect.bottom + boundingRect.height)
	{
		m_Velocity.y = -abs(m_Velocity.y);
	}
	m_IsInSafeArea = IsInSafeArea(safeRect);
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest( const Point2f& pos )
{
	if (utils::IsPointInRect(pos, Rectf{ m_Position.x,m_Position.y,m_pSmileyTexture->GetWidth() / 4,m_pSmileyTexture->GetHeight() }))
	{
		m_IsSleeping = !m_IsSleeping;
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping( )
{
	return m_IsSleeping; 
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition( )
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest( bool isHighest )
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed( )
{
	m_Velocity.x = m_Velocity.x * 1.05f;
	m_Velocity.y = m_Velocity.y * 1.05f;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed( )
{
	m_Velocity.x = m_Velocity.x * 0.95f;
	m_Velocity.y = m_Velocity.y * 0.95f;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea( const Rectf& safeRect )
{
	return utils::IsPointInRect(m_Position,safeRect); 
}



