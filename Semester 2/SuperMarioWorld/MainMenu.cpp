#include "pch.h"
#include "MainMenu.h"
#include "Structs.h"
#include "Texture.h"
#include "utils.h"
#include "MenuButton.h"
#include "SettingsButton.h"
#include <iostream>

MainMenu::State MainMenu::m_State{State::titlescreen};
bool MainMenu::m_IsQWERTY{ true };

bool MainMenu::IsQWERTY()
{
	return m_IsQWERTY;
}

MainMenu::MainMenu(const Window& window)
	:m_Window{window}
	,m_pCreditsTexture{}
	,m_TransitioningTo{State::titlescreen}
	,m_Selecting{State::off}
	,m_TransitionAlpha{0}
	,m_pPlayButton{ new MenuButton() }
	,m_pSettingsButton{ new MenuButton() }
	,m_pBackButton{ new MenuButton() }
	,m_pIsQWERTYButton{ new SettingsButton(m_IsQWERTY)}
	,m_pTitlescreenTitle{ new Texture{"Resources/TitleScreenTitle.png"}}
{
	std::string fontPath{ "Resources/consola.ttf" };
	Color4f textColor{ 1,1,1,1 };
	int fontSize{ 32 };
	float borderScale{ 1.2f };

	m_pPlayButton->SetTexture(new Texture{ "Play",fontPath,fontSize,textColor });
	m_pSettingsButton->SetTexture(new Texture{ "Settings",fontPath,fontSize,textColor });
	m_pBackButton->SetTexture(new Texture{ "Back",fontPath,fontSize,textColor });
	m_pIsQWERTYButton->SetTexture( new Texture{ "QWERTY",fontPath,fontSize,textColor } );

	m_pCreditsTexture = new Texture{"Made by Reï Messely", fontPath,fontSize / 2,textColor};

	m_pPlayButton->AdjustRectToTexture(borderScale);
	m_pSettingsButton->AdjustRectToTexture(borderScale);
	m_pBackButton->AdjustRectToTexture(borderScale);

	m_pPlayButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) });
	m_pSettingsButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) * 0.8f });
	m_pBackButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) * 0.8f });
	m_pIsQWERTYButton->CenterTo( Point2f{ m_Window.width / 2, (m_Window.height / 2) * 1.2f });
}
MainMenu::~MainMenu()
{
	delete m_pPlayButton;
	m_pPlayButton = nullptr;
	delete m_pSettingsButton;
	m_pSettingsButton = nullptr;
	delete m_pBackButton;
	m_pBackButton = nullptr;
	delete m_pIsQWERTYButton;
	m_pIsQWERTYButton = nullptr;
	
	delete m_pCreditsTexture;
	m_pCreditsTexture = nullptr;
	delete m_pTitlescreenTitle;
	m_pTitlescreenTitle = nullptr;
}

void MainMenu::Draw() const
{
	// Don't do anything if the MainMenu isn't active
	if (m_State == State::off) return;
	// Titlescreen objects
	if (m_State == State::titlescreen)
	{
		DrawBackground();
		m_pPlayButton->SetActive(false);
		m_pSettingsButton->SetActive(false);
		m_pTitlescreenTitle->Draw(Point2f{ m_Window.width / 2 - m_pTitlescreenTitle->GetWidth() / 2, m_Window.height * 0.8f - m_pTitlescreenTitle->GetHeight() / 2 });

		switch (m_Selecting)
		{
		case State::playing:
			m_pPlayButton->SetActive(true);
			break;
		case State::settings:
			m_pSettingsButton->SetActive(true);
			break;
		}

		m_pPlayButton->Draw();
		m_pSettingsButton->Draw();

		m_pCreditsTexture->Draw(Point2f{ 10,10 });
	}
	// Settings objects
	else if (m_State == State::settings)
	{
		DrawBackground();
		m_pBackButton->SetActive(false);
		switch (m_Selecting)
		{
		case State::settings:
			m_pBackButton->SetActive(true);
			break;
		}
		m_pBackButton->Draw();

		m_pIsQWERTYButton->Draw();

		m_pCreditsTexture->Draw(Point2f{ 10,10 });
	}
	// Fading 
	if (m_TransitioningTo == State::playing)
	{
		utils::SetColor(Color4f{0,0,0,m_TransitionAlpha});
		utils::FillRect(Rectf{0,0,m_Window.width,m_Window.height});
	}
}

void MainMenu::CheckClicks(const SDL_MouseButtonEvent& e)
{
	// If we're playing the game, we shouldn't check for clicks on the MainMenu
	if (m_State == State::playing) return;
	// Don't check for clicks if we're transitioning to playing
	if (m_TransitioningTo == State::playing) return;

	Point2f mousePos = Point2f{ float(e.x),float(e.y) };

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		// Clicking on Play
		if (m_pPlayButton->IsInside(mousePos) && m_State == State::titlescreen)
		{
			m_TransitioningTo = State::playing;
		}
		// Clicking on Settings
		else if (m_pSettingsButton->IsInside(mousePos) && m_State != State::settings)
		{
			m_State = State::settings;
		}
		// Clicking on Back
		else if (m_pBackButton->IsInside(mousePos) && m_State == State::settings)
		{
			m_State = State::titlescreen;
		}
		// Clicking on QWERTY setting
		else if (m_pIsQWERTYButton->IsInside(mousePos) && m_State == State::settings)
		{
			m_IsQWERTY = !m_IsQWERTY;
		}
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void MainMenu::Update(float elapsedSec)
{
	if (m_TransitioningTo == State::playing)
	{
		float alphaStep{ 0.5f };
		if (m_State != State::playing) m_TransitionAlpha += alphaStep * elapsedSec;
		else m_TransitionAlpha -= alphaStep * elapsedSec;
		if (m_TransitionAlpha >= 1.0f)
		{
			m_State = State::playing;
		}
		else if (m_TransitionAlpha <= 0)
		{
			m_TransitioningTo = State::off;
			m_TransitionAlpha = 0;
		}
	}
}

void MainMenu::CheckSelect(const Point2f& mousePos)
{
	// If we're playing, no need to check input on mainmenu
	if (m_TransitioningTo == State::playing) return;
	if (m_pPlayButton->IsInside(mousePos))
	{
		m_Selecting = State::playing;
	}
	else if (m_State == State::settings)
	{
		if (m_pBackButton->IsInside(mousePos)) m_Selecting = State::settings;
		else m_Selecting = State::off;
	}
	else if (m_pSettingsButton->IsInside(mousePos))
	{
		m_Selecting = State::settings;
	}
	else m_Selecting = State::off;
}

void MainMenu::DrawBackground() const
{
	utils::SetColor(Color4f{ 0,0,0,1 });
	utils::FillRect(Rectf{ 0,0,m_Window.width,m_Window.height });
}
