#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "ArrayApplications - Messely, Reï - 1DAE22" };

// Change the window dimensions here
float g_WindowWidth{ 500 };
float g_WindowHeight{ 300 };
#pragma endregion gameInformation

// Texture g_Font{};
// TextureFromString("Hello World!", "Resources/DIN-Light.otf", 34, Color4f{ 1,0,0,1 }, g_HelloTexture);
// DrawTexture(g_HelloTexture, g_DAEPoint);
// DeleteTexture(g_HelloTexture);

#pragma region ownDeclarations
// Declare your own global variables here
const  int g_MaxNumberOfClickedPos{ 5 };
int g_CurrentClickedPosIdx{ 0 };
Point2f g_ClickedPositions[g_MaxNumberOfClickedPos]{};

struct AngleSpeed
{
	float angle{};
	float speed{};
};
const int g_PentagramsMaxSize{ 5 };
const float g_PentagramRadius{ 100 };
const Point2f g_PentagramCenterPoint{ 400, 150 };
AngleSpeed g_Pentagrams[g_PentagramsMaxSize]{};

const unsigned int g_RandStatAmount{ 6 };
unsigned int g_RandStats[g_RandStatAmount]{};
Texture g_RandStatTextures[g_RandStatAmount];
const Color4f g_SoftYellow{ 0.8f,0.8f,0.4f,1 };

const int g_MaxNumberOfLastPos{ 10 };
int g_CurrentMousePosIdx{ 0 };
Point2f g_LastMousePos[g_MaxNumberOfLastPos]{};

const int g_CellAmount{ 12 };
bool g_ClickedCells[g_CellAmount]{};
Rectf g_Cells[g_CellAmount]{};

// Declare your own functions here
void AddPointToArray(Point2f* arr, const int arrSize, const Point2f& mousePos, int& currentIdx);
void DrawClickedPoints(const Point2f* pClickedPositions, const int arrSize);

void InitPentagrams(AngleSpeed* pArr, const int arrSize);
void DrawPentagrams(AngleSpeed* pPentagrams, const int arrSize, const Point2f& centerPoint, float rad);
void UpdatePentagrams(AngleSpeed* pPentagrams, const int arrSize, float elapsedSec);

void InitRandStatsToFont();
void UpdateRandStats();
void DrawRandStats();

void DrawMousePos(Point2f* arr, const int arrSize);

int GetIndex(int rowIdx, int colIdx, int nrCols);
void InitGrid(Rectf* pRects, bool* pBools ,const int rectSize);
void DrawGrid(Rectf* pRects, bool* pBools, const int rectSize);
void UpdateGrid(Rectf* pRects, bool* pBools, const int rectSize, const Point2f& pos);
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
