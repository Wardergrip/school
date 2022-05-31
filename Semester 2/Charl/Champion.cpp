#include "pch.h"
#include "Champion.h"

#include "utils.h"
#include "ExampleAbility.h"

Champion::Champion(const Window& window)
	:m_pAbilityInterface{new AbilityInterface(window)}
{
	m_Hitbox = Rectf{ 0,0,20,20 };
	CenterHitboxToPosition();

	m_pAbilityInterface->AssignAbility(AbilityKey::Q, new ExampleAbility("Q", this->m_Transform.location));
}

Champion::~Champion()
{
	delete m_pAbilityInterface;
	m_pAbilityInterface = nullptr;
}

void Champion::Draw() const
{
	Unit::Draw();
	m_pAbilityInterface->Draw();
}

void Champion::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	OnMouseDownBasic(e);
}

void Champion::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	OnMouseUpBasic(e);
}

void Champion::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	OnMouseMotionBasic(e);
}

void Champion::OnKeyDown(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
	AbilityKey key{ GetAppropriateAbilityKey(e) };
	m_pAbilityInterface->OnPressAbility(key,mousePos);
}

void Champion::OnKeyHold(float elapsedSec, const Uint8* pStates, const Point2f& mousePos)
{
	if (pStates[SDL_SCANCODE_Q])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::Q, mousePos, elapsedSec);
	}
	if (pStates[SDL_SCANCODE_W])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::W, mousePos, elapsedSec);
	}
	if (pStates[SDL_SCANCODE_E])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::E, mousePos, elapsedSec);
	}
	if (pStates[SDL_SCANCODE_R])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::R, mousePos, elapsedSec);
	}
	if (pStates[SDL_SCANCODE_D])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::D, mousePos, elapsedSec);
	}
	if (pStates[SDL_SCANCODE_F])
	{
		m_pAbilityInterface->OnHoldingAbility(AbilityKey::F, mousePos, elapsedSec);
	}
}

void Champion::OnKeyUp(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
	AbilityKey key{ GetAppropriateAbilityKey(e) };
	m_pAbilityInterface->OnReleaseAbility(key,mousePos);
}

AbilityKey Champion::GetAppropriateAbilityKey(const SDL_KeyboardEvent& e) const
{
	AbilityKey key{ AbilityKey::undefined };
	switch (e.keysym.sym)
	{
	case SDLK_q:
		key = AbilityKey::Q;
		break;
	case SDLK_w:
		key = AbilityKey::W;
		break;
	case SDLK_e:
		key = AbilityKey::E;
		break;
	case SDLK_r:
		key = AbilityKey::R;
		break;
	case SDLK_d:
		key = AbilityKey::D;
		break;
	case SDLK_f:
		key = AbilityKey::F;
		break;
	}
	return key;
}