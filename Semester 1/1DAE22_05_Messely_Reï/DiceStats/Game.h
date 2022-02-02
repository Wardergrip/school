#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "DiceStats - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 500 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
#pragma region OneDieThrowTrackers
int g_OneDieThrewOne{};
int g_OneDieThrewTwo{};
int g_OneDieThrewThree{};
int g_OneDieThrewFour{};
int g_OneDieThrewFive{};
int g_OneDieThrewSix{};
#pragma endregion
#pragma region TwoDiceThrowTrackers
int g_TwoDiceThrewTwo{};
int g_TwoDiceThrewThree{};
int g_TwoDiceThrewFour{};
int g_TwoDiceThrewFive{};
int g_TwoDiceThrewSix{};
int g_TwoDiceThrewSeven{};
int g_TwoDiceThrewEight{};
int g_TwoDiceThrewNine{};
int g_TwoDiceThrewTen{};
int g_TwoDiceThrewEleven{};
int g_TwoDiceThrewTwelve{};
#pragma endregion
// Declare your own functions here
void ThrowOneDie();
void ThrowTwoDice();
void VisualiseOneDie();
void VisualiseTwoDice();
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
