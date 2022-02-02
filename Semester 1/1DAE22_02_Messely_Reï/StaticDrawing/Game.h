#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "StaticDrawing - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 600 };
float g_WindowHeight{ 450 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
#pragma region Colors
const Color4f g_BackgroundColor{ 50 / 255.0f, 20 / 255.0f, 50 / 255.0f , 1.0f };
const Color4f g_Black{ 0,0,0, 1.0f};
const Color4f g_White{ 1.0f,1.0f,1.0f, 1.0f };
const Color4f g_Yellow{ 1.0f,1.0f,0, 1.0f};
const Color4f g_Red{ 1.0f,0,0, 1.0f};
const Color4f g_HouseBorder{ 232 / 255.0f, 187 / 255.0f, 190 / 255.0f, 1.0f };
const Color4f g_HouseColor{ g_Red };
const Color4f g_HouseRoofColor{ g_Red };
const Color4f g_FlagBorder{ 213 / 255.0f, 183 / 255.0f, 190 / 255.0f, 1.0f };
const Color4f g_CheckersBorder{ 219 / 255.0f, 213 / 255.0f, 219 / 255.0f, 1.0f };
const Color4f g_BandBorder{ g_Yellow };
const Color4f g_Pentagram{ 255 / 255.0f, 0 / 255.0f, 128 / 255.0f, 1.0f };
#pragma endregion
#pragma region House variables
const float g_HouseX{10};
const float g_HouseY{300};
const float g_HouseW{260};
const float g_HouseH{120};
#pragma endregion
#pragma region Flag Variables
const float g_FlagW{ 250 };
const float g_FlagH{ 110 };
const float g_FlagX{ 15 }; 
const float g_FlagY{ g_WindowHeight / 2 - g_FlagH / 2 }; 
#pragma region Checker Variables
const float g_CheckersSize{110};
const float g_CheckersX{15}; 
const float g_CheckersY{20}; 
#pragma endregion
#pragma region ColorBand Variables
const float g_BandX{g_WindowWidth / 2 + 10}; 
const float g_BandY{2*(g_WindowHeight) / 3 + 10};  
const float g_BandW{250};  
const float g_BandH{(4*g_BandW)/9}; 
#pragma endregion
#pragma region Pentagram Variables
const Point2f g_PentagramCenterpoint{ g_WindowWidth / 2 + 150, g_WindowHeight / 2 - 20 };
const float g_PentagramRadius{50};
const float g_StartingAngle{ 2 };
const float g_PentagramThickness{ 1 };
#pragma endregion
#pragma region ColumnChart Variables
const float g_ColumnX{g_WindowWidth /2 + 10};
const float g_ColumnY{20};
const float g_ColumnW{200};
const float g_ColumnMaxHeight{100};
int g_ZeroToTwenty{40};
int g_TwentyoneToForty{50};
int g_FortyoneToSixty{50};
int g_SixtyPlus{10};
#pragma endregion



// Declare your own functions here
void DrawHouse();
void DrawFlag();
void DrawCheckerPattern();
void DrawColorBand();
void DrawPentagram();
void DrawColumnChart();
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
