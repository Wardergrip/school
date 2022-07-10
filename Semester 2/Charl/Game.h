#pragma once

#include <vector>

class Unit;
class Champion;
class ProjectileManager;
class HUD;
class CameraManager;

class SmartTextComponent;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	Point2f m_LastMousePos;

	Champion* m_TestingChamp;
	ProjectileManager* m_ProjectileManager;
	std::vector<Unit*> m_Units;

	HUD* m_pInGameHUD;
	SmartTextComponent* m_Orientation;
	SmartTextComponent* m_FPS;
	CameraManager* m_pCameraManager;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
};