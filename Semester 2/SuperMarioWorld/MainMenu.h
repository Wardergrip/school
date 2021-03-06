#pragma once
struct Window;
class Texture;
class MenuButton;
class SettingsButton;

class MainMenu final
{
public:
	enum class State
	{
		off,
		playing,
		settings,
		titlescreen
	};

	static State m_State;

	explicit MainMenu(const Window& window, State startingState);
	MainMenu(const MainMenu& m) = delete;
	MainMenu& operator=(const MainMenu& m) = delete;
	MainMenu(MainMenu&& m) = delete;
	MainMenu& operator=(MainMenu&& m) = delete;
	~MainMenu();
	
	void Draw() const;
	void CheckUpClicks(const SDL_MouseButtonEvent& e);
	void CheckDownClicks(const SDL_MouseButtonEvent& e);
	void CheckSelect(const Point2f& mousePos);
	void Update(float elapsedSec);

	static bool IsSoundOn();

	std::string ToXML() const;

private:
	// +-----+ DATA MEMBERS +-----+

	static bool m_IsSoundOn;
	bool m_WipingButtonActive; 
	bool m_DisplayPBButtonActive;

	const Window& m_Window;

	MenuButton* m_pPlayButton;
	MenuButton* m_pSettingsButton;
	MenuButton* m_pBackButton;

	SettingsButton* m_pWipeButton;
	SettingsButton* m_pDisplayPBButton;
	SettingsButton* m_pSoundOnButton;

	Texture* m_pCreditsTexture;

	// +-----+ FLUFF +-----+

	State m_TransitioningTo;
	State m_Selecting;
	float m_TransitionAlpha;

	Texture* m_pTitlescreenTitle;
	Texture* m_pTitlescreenBorder;


	// +-----+ FUNCTIONS +-----+

	void DrawBackground() const;
};

