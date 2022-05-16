#include "pch.h"
#include "MainMenu.h"
#include "Structs.h"
#include "Texture.h"
#include "utils.h"
#include "MenuButton.h"
#include "SettingsButton.h"
#include <iostream>
#include "XMLProcessor.h"
#include "SoundManager.h"

MainMenu::State MainMenu::m_State{State::titlescreen};
bool MainMenu::m_IsSoundOn{ true };

MainMenu::MainMenu(const Window& window, State startingState)
	:m_Window{window}
	,m_pCreditsTexture{}
	,m_TransitioningTo{State::off}
	,m_Selecting{State::off}
	,m_TransitionAlpha{0}
	,m_pPlayButton{ new MenuButton() }
	,m_pSettingsButton{ new MenuButton() }
	,m_pBackButton{ new MenuButton() }
	,m_pWipeButton{ new SettingsButton(m_WipingButtonActive)}
	,m_pTitlescreenTitle{ new Texture{"Resources/TitleScreenTitle.png"}}
	,m_pTitlescreenBorder{new Texture{"Resources/TitleScreenBorder.png"}}
	,m_pDisplayPBButton{new SettingsButton(m_DisplayPBButtonActive)}
	,m_pSoundOnButton{new SettingsButton(m_IsSoundOn)}
	,m_WipingButtonActive{false}
	,m_DisplayPBButtonActive{false}
{
	m_State = startingState;
	std::string fontPath{ "Resources/consola.ttf" };
	Color4f textColor{ 1,1,1,1 };
	int fontSize{ 32 };
	float borderScale{ 1.2f };

	m_pPlayButton->SetTexture(new Texture{ "Play",fontPath,fontSize,textColor });
	m_pSettingsButton->SetTexture(new Texture{ "Settings",fontPath,fontSize,textColor });
	m_pBackButton->SetTexture(new Texture{ "Back",fontPath,fontSize,textColor });
	m_pWipeButton->SetTexture( new Texture{ "Wipe Save",fontPath,fontSize,textColor } );
	m_pDisplayPBButton->SetTexture(new Texture{ "Display PB",fontPath,fontSize,textColor });
	m_pSoundOnButton->SetTexture(new Texture{ "Sound",fontPath,fontSize,textColor });

	m_pCreditsTexture = new Texture{"Made by Reï Messely", fontPath,fontSize / 2,textColor};

	m_pPlayButton->AdjustRectToTexture(borderScale);
	m_pSettingsButton->AdjustRectToTexture(borderScale);
	m_pBackButton->AdjustRectToTexture(borderScale);

	m_pPlayButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) });
	m_pSettingsButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) * 0.8f });
	m_pBackButton->CenterTo(Point2f{ m_Window.width / 2,(m_Window.height / 2) * 0.8f });
	m_pWipeButton->CenterTo( Point2f{ m_Window.width / 2 - 100, (m_Window.height / 2) * 1.2f });
	m_pSoundOnButton->CenterTo( Point2f{ m_Window.width / 2 + 100, (m_Window.height / 2) * 1.2f });
	m_pDisplayPBButton->CenterTo(Point2f{ m_Window.width - 150,70 });

#pragma region SettingsFile
	{
		using XMLP = XMLProcessor;
		std::string filepath{ XMLP::GetFilePath() };
		std::string output{};
		XMLP::ChangeFilePath("Resources/settings.xml");
		if (!XMLP::ReadFile(output)) throw "Wrong filepath";

		m_IsSoundOn = bool(XMLP::GetAttributeValue("sound", output));
		SoundManager::ToggleSound(m_IsSoundOn); // Adjust soundsetting to the newly read setting
		XMLP::ChangeFilePath(filepath);
	}
#pragma endregion
}
MainMenu::~MainMenu()
{
	delete m_pPlayButton;
	m_pPlayButton = nullptr;
	delete m_pSettingsButton;
	m_pSettingsButton = nullptr;
	delete m_pBackButton;
	m_pBackButton = nullptr;
	delete m_pWipeButton;
	m_pWipeButton = nullptr;
	
	delete m_pCreditsTexture;
	m_pCreditsTexture = nullptr;
	delete m_pTitlescreenTitle;
	m_pTitlescreenTitle = nullptr;
	delete m_pTitlescreenBorder;
	m_pTitlescreenBorder = nullptr;
	delete m_pDisplayPBButton;
	m_pDisplayPBButton = nullptr;
	delete m_pSoundOnButton;
	m_pSoundOnButton = nullptr;

	{
		using XMLP = XMLProcessor;
		std::string filepath{ XMLP::GetFilePath() };
		XMLP::ChangeFilePath("Resources/settings.xml");
		XMLP::SaveToFile(ToXML());
		XMLP::ChangeFilePath(filepath);
	}
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

		glPushMatrix();
		{
			float scale{ 1.5f };
			glTranslatef(m_Window.width / 2 - scale * (m_pTitlescreenTitle->GetWidth() / 2), m_Window.height * 0.7f - scale * (m_pTitlescreenTitle->GetHeight() / 2), 0);
			glScalef(scale, scale, 0);
			m_pTitlescreenTitle->Draw();
		}
		glPopMatrix();

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

		m_pCreditsTexture->Draw(Point2f{ 50,50 });
		m_pDisplayPBButton->Draw();
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

		m_pWipeButton->Draw();

		m_pSoundOnButton->Draw();

		m_pCreditsTexture->Draw(Point2f{ 50,50 });
	}
	// Fading 
	if (m_TransitioningTo == State::playing)
	{
		utils::SetColor(Color4f{0,0,0,m_TransitionAlpha});
		utils::FillRect(Rectf{0,0,m_Window.width,m_Window.height});
	}
}

void MainMenu::CheckUpClicks(const SDL_MouseButtonEvent& e)
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
		else if (m_pWipeButton->IsInside(mousePos) && m_State == State::settings)
		{
			XMLProcessor::WipeAndCleanSave();
			std::cout << "Current personalbest is reset\n";
		}
		// Clicking on Sound setting
		else if (m_pSoundOnButton->IsInside(mousePos) && m_State == State::settings)
		{
			m_IsSoundOn = !m_IsSoundOn;
			SoundManager::ToggleSound(m_IsSoundOn);
		}
		// Clicking on PBdisplay
		else if (m_pDisplayPBButton->IsInside(mousePos) && m_State == State::titlescreen)
		{
			XMLProcessor::DisplayPersonalBest();
		}
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
	m_WipingButtonActive = false;
	m_DisplayPBButtonActive = false;
}

void MainMenu::CheckDownClicks(const SDL_MouseButtonEvent& e)
{
	// If we're playing the game, we shouldn't check for clicks on the MainMenu
	if (m_State == State::playing) return;
	// Don't check for clicks if we're transitioning to playing
	if (m_TransitioningTo == State::playing) return;

	Point2f mousePos = Point2f{ float(e.x),float(e.y) };

	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (m_pWipeButton->IsInside(mousePos) && m_State == State::settings)
		{
			m_WipingButtonActive = true;
		}
		else if (m_pDisplayPBButton->IsInside(mousePos) && m_State == State::titlescreen)
		{
			m_DisplayPBButtonActive = true;
		}
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

bool MainMenu::IsSoundOn()
{
	return m_IsSoundOn;
}

std::string MainMenu::ToXML() const
{
	std::string output;
	std::string helper{ "\"" };

	output += "<settings\n";
	output += "\t"; // horizontal tab
	output += "sound=" + helper + std::string(m_IsSoundOn ? "1" : "0") + helper +'\n';

	output += "/>";

	return output;
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
	glPushMatrix();
	{
		Vector2f scalingVector{ m_Window.width / m_pTitlescreenBorder->GetWidth(),m_Window.height / m_pTitlescreenBorder->GetHeight() };
		glScalef(scalingVector.x, scalingVector.y, 0);
		m_pTitlescreenBorder->Draw();
	}
	glPopMatrix();
}
