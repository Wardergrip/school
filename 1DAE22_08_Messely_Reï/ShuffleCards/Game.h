#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "ShuffleCards - Messely, Re� - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 1000 };
float g_WindowHeight{ 600 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
const int g_AmountOfCards{ 52 };
Texture g_CardTextures[g_AmountOfCards];
const float g_CardScale{ 1 };
const Rectf g_DefaultCard{ 0,0,140,190 };
Rectf g_CardRects[g_AmountOfCards];
// Declare your own functions here
int GetIndex(int rowIdx, int colIdx, int nrCols);

void InitCards();
void DeleteCards();
void DrawCards();
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
