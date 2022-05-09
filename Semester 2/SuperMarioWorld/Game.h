#pragma once
#include "Player.h"
#include "Camera.h"

class MainMenu;
class Level;
class Mario;
class Coin;
class FireFlower;
class Mushroom;
class HUD;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Draw( ) const;
	void Update( float elapsedSec );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	MainMenu* m_pMainMenu;

	Camera m_Camera;
	Player m_Player;
	HUD* m_pHUD;

	Level* m_pLevel;

	std::string m_PersonalBestFilePath;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void DisplayInfo();
};