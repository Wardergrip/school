#include "pch.h"
#include "Ability.h"

#include "utils.h"
using namespace utils;

#include "Texture.h"
#include "Timer.h"
#include "CircleProgression.h"

#include <iostream>

// STATICS

ProjectileManager* Ability::c_ProjectileManagerRef{ nullptr };

void Ability::InitProjManager(ProjectileManager* projMan)
{
	c_ProjectileManagerRef = projMan;
}

// NON STATICS

Ability::Ability(Type type, const std::string& key, const std::string& name, float cooldown)
	:m_Type{type}
	,m_ShowTelegraph{false}
	,m_Cooldown{ new Timer{cooldown} }
	,m_Name{ name }
	,m_pButtonKeyTexture{ new Texture{key,"Resources/consola.ttf",20,Color4f{1,0,0,1}} }
{
	m_pCircleProgression = new CircleProgression{ Point2f{25,25}, *m_Cooldown,true};
	m_pCircleProgression->FlipX();
	m_pCircleProgression->SetRad(23);
}

Ability::~Ability()
{
	delete m_pButtonKeyTexture;
	m_pButtonKeyTexture = nullptr;
	delete m_Cooldown;
	m_Cooldown = nullptr;
	delete m_pCircleProgression;
	m_pCircleProgression = nullptr;
}

void Ability::DrawUI() const
{
	SetColor(Color4f{ 0.9f, 0.9f, 0.9f, 1 });
	DrawRect(Rectf{ 0,0,50,50 });
	if (this)
	{
		if (!m_Cooldown->IsDone())
		{
			SetColor(Color4f{ 1,1,1,0.5f });
			m_pCircleProgression->Draw();
		}
	}
	if (this == nullptr) return;
	m_pButtonKeyTexture->Draw(Point2f{2,1});
	DrawIcon();
}
