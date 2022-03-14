#include "pch.h"
#include "Diamond.h"
#include "Texture.h"
#include "utils.h"
using namespace utils;

#include <iostream>

Texture* Diamond::m_pDiamondTexture{nullptr};
unsigned int Diamond::m_Instances{0};

Diamond::Diamond(const Point2f& startingPos)
	:m_IsSelected{false}
	,m_Translation{ startingPos.x, startingPos.y }
	,m_Angle{0}
	,m_Scale{1}
	,m_CurrentMatrix{}
	,m_LastMatrix{}
	,m_TransVertices{}
{
	++m_Instances;
	if (m_Instances == 1)
	{
		m_pDiamondTexture = new Texture{ "Resources/Diamond.png" };
	}
	const float diamondSize{ 48.f };
	m_Vertices.push_back(Point2f{ 0, diamondSize / 2 });
	m_Vertices.push_back(Point2f{ diamondSize / 2, diamondSize });
	m_Vertices.push_back(Point2f{ diamondSize, diamondSize / 2 });
	m_Vertices.push_back(Point2f{ diamondSize / 2, 0 });

	Matrix2x3 matTrans, matRotate, matScale, matCenter;
	matTrans.SetAsTranslate(m_Translation);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matCenter.SetAsTranslate(-24.f, -24.f);
	m_LastMatrix = matTrans * matRotate * matScale * matCenter;
}

Diamond::~Diamond()
{
	--m_Instances;
	if (m_Instances == 0)
	{
		delete m_pDiamondTexture;
		m_pDiamondTexture = nullptr;
	}
	m_Vertices.clear();
	m_TransVertices.clear();
}

void Diamond::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Translation.x, m_Translation.y, 0.f);
		glRotatef(m_Angle,0,0,1.f);
		glScalef(m_Scale, m_Scale, 1);
		glTranslatef(-24.f, -24.f, 0.f);
		m_pDiamondTexture->Draw();
	}
	glPopMatrix();

	if (m_IsSelected) SetColor(Color4f{ 1.f,0,0,1.f });
	else SetColor(Color4f{ 0,0,1.0f,1.f });
	DrawPolygon(m_TransVertices, true, 2.0f);
}

void Diamond::Update(float elapsedSec)
{
	const float rotationSpeed{ 60 };
	const float movementSpeed{ 120 };
	const float scaleSpeed{ 3 };
	// Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_A])
	{
		if(m_IsSelected) m_Angle += rotationSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_D])
	{
		if (m_IsSelected) m_Angle -= rotationSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_W])
	{
		if (m_IsSelected) m_Scale *= 1 + (scaleSpeed * elapsedSec);
	}
	if (pStates[SDL_SCANCODE_S])
	{
		if (m_IsSelected) m_Scale /= 1 + (scaleSpeed * elapsedSec);
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		if (m_IsSelected) m_Translation.y += movementSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		if (m_IsSelected) m_Translation.y -= movementSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		if (m_IsSelected) m_Translation.x -= movementSpeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		if (m_IsSelected) m_Translation.x += movementSpeed * elapsedSec;
	}

	Matrix2x3 matTrans, matRotate, matScale, matCenter;
	matTrans.SetAsTranslate(m_Translation);
	matRotate.SetAsRotate(m_Angle);
	matScale.SetAsScale(m_Scale);
	matCenter.SetAsTranslate(-24.f, -24.f);
	m_CurrentMatrix = matTrans * matRotate * matScale * matCenter;
	
	m_TransVertices = m_CurrentMatrix.Transform(m_Vertices);

}

void Diamond::SwitchSelect()
{
	m_IsSelected = !m_IsSelected;
}

void Diamond::SetSelect(bool state)
{
	if (!m_IsSelected) return;
	m_IsSelected = state;
}

void Diamond::AddTranslation(const Vector2f& translation)
{
	if (!m_IsSelected) return;
	m_Translation += translation;
}

void Diamond::AddRotation(float angle)
{
	if (!m_IsSelected) return;
	m_Angle += angle;
	if (m_Angle >= 360.f) m_Angle -= 360.f;
}

void Diamond::AddScale(float scale)
{
	if (!m_IsSelected) return;
	m_Scale += scale;
}

void Diamond::ResetTransformation()
{
	m_CurrentMatrix = m_LastMatrix;
	m_Translation = m_LastMatrix.orig;
	m_Scale = 1;
	m_Angle = 0;
}

bool Diamond::IsInside(const Point2f& pos) const
{
	return IsPointInPolygon(pos, m_TransVertices);
}

bool Diamond::IsSelected() const
{
	return m_IsSelected;
}
