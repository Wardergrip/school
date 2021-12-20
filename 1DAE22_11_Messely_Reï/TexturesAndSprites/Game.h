#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "TexturesAndSprites - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
enum class AnimationState
{
	idle,
	running,
	jumping
};

class Sprite; // Class forward declaration
const int g_AmountOfSprites{ 5 };
Sprite* g_pSprites[g_AmountOfSprites];

std::string g_FilePathRunningKnight{ "Resources/RunningKnight.png" };
std::string g_FilePathTibo{ "Resources/Tibo.png" };

class SuperSprite; // class forward declaration
SuperSprite* g_Mario{ nullptr };
AnimationState g_MarioState{ AnimationState::idle };

std::string g_FilePathMarioIdle{ "Resources/marioIdle.png" };
std::string g_FilePathMarioJump{ "Resources/marioJump.png" };
std::string g_FilePathMarioRun{ "Resources/marioRun.png" };


// Declare your own functions here

#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
