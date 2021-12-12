#pragma once

// When updating this file, change the following:
// 
// 
// 

enum class TowerType
{
	basic,
	sniper,
	minigun,
	countTowerTypes
};

struct TowerBarrel
{
	Point2f point{};
	float barrelSize{};
	float length{};
	float angle{};
	Color4f color{};
	float radius{};
	float attackDamage{};
	float attackSpeed{};
	float timeSinceLastAttack{};
	int cost{};
};
struct Tower
{
	Texture baseTexture{};
	Rectf destRectf{};
	Rectf srcRectf{};
	TowerBarrel tb{};
};

Texture g_CheckmarkTexture;
Texture g_CrossTexture;
Texture g_SliderLeftTexture;
Texture g_SliderRightTexture;

UserInterface g_OpenButton{};
UserInterface g_PlayButton{};
UserInterface g_StartWaveText{};

UserInterface g_ErrorMessage{};
float g_ErrorElapsedTime{};
float g_ErrorTime{ 10 };

int g_AmountOfDefaultTowers{};
Tower* g_pDefaultTowers{ nullptr };
Tower* g_pBuyMenuTowers{ nullptr };
Tower* g_pBoughtTowers{ nullptr };
bool* g_pBought{ nullptr };

Tower g_BuyTowerDisplay{};
bool g_IsBuyTowerDisplay{ false };
Point2f g_BuyPos{};


const Rectf g_BuyMenuRectf{ g_WindowWidth - 2 * g_WindowWidth / 10,0,2 * (g_WindowWidth / 10), g_WindowHeight };
const Color4f g_BuyMenuColor4f{ 0.4f,0.4f,0.4f,0.8f };
const float g_BuyMenuButtonScale{ 2 };

bool g_IsBuyMenuActive{ true };

void InitTurrets();
void DeleteTurrets();
void DrawTurretBarrel(const TowerBarrel& tb);
void UpdateTurretBarrel(Tower& t, const Point2f& enemyP);
void UpdateTurretBarrel(Tower& t, float elapsedSec);
void UpdateTurretBarrel(Tower& t);
void DrawTurret(const Tower& t);

void InitBuyMenu();
void DrawBuyMenu();
void UpdateBuyMenu(float elapsedSec);
void DeleteBuyMenu();

void UpdateBuy();
void BuyTower(const Point2f& pos, const Tower& boughtTower);
void DrawBoughtTowers();
void UpdateBoughtTowers(float elapsedSec);
void ShootTower(Tower& t, Enemy& e, float elapsedSec);
void ResetBoughtTowers();

void DisplayWaveNr();
void DisplayMoney();
int ASCIINumToInt(int ascii);

void DisplayErrorMessage(const std::string& msg, float secondsDisplayed);
void DrawErrorMessage();

void DrawPriceTextures();

void StartRei();
void DrawRei();
void UpdateRei(float elapsedSec);
void EndRei();

// ----------------------------------------------------------------------

void InitTurrets()
{
	g_AmountOfDefaultTowers = int(TowerType::countTowerTypes);
	g_pDefaultTowers = new Tower[g_AmountOfDefaultTowers];
	g_pBoughtTowers = new Tower[g_WorldTileAmount];
	g_pBought = new bool[g_WorldTileAmount];
	float scale{ g_WorldTilescale * 0.8f };

	for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
	{
		g_pDefaultTowers[i].baseTexture = g_pTileTextures[int(TileType::towerBase)];

		g_pDefaultTowers[i].srcRectf.width = g_pDefaultTowers[i].baseTexture.width;
		g_pDefaultTowers[i].srcRectf.height = g_pDefaultTowers[i].baseTexture.height;
		g_pDefaultTowers[i].srcRectf.bottom = g_pDefaultTowers[i].srcRectf.height;

		g_pDefaultTowers[i].destRectf.width = g_pDefaultTowers[i].srcRectf.width * scale;
		g_pDefaultTowers[i].destRectf.height = g_pDefaultTowers[i].srcRectf.height * scale;

		switch (TowerType(i))
		{
		case TowerType::basic:
			g_pDefaultTowers[i].tb.color = Color4f{ 0.8f,0,0,1 };
			g_pDefaultTowers[i].tb.radius = 100;
			g_pDefaultTowers[i].tb.attackDamage = 25;
			g_pDefaultTowers[i].tb.attackSpeed = 1;
			g_pDefaultTowers[i].tb.cost = 100;

			g_pDefaultTowers[i].tb.barrelSize = 10;
			g_pDefaultTowers[i].tb.length = 25;
			g_pDefaultTowers[i].tb.point = Point2f{g_pDefaultTowers[i].destRectf.left + g_pDefaultTowers[i].destRectf.width / 2, g_pDefaultTowers[i].destRectf.bottom + g_pDefaultTowers[i].destRectf.height / 2 };
			break;
		case TowerType::sniper:
			g_pDefaultTowers[i].tb.color = Color4f{ 0.8f,0.8f,0.4f,1 };
			g_pDefaultTowers[i].tb.radius = 200;
			g_pDefaultTowers[i].tb.attackDamage = 75;
			g_pDefaultTowers[i].tb.attackSpeed = 2.5f;
			g_pDefaultTowers[i].tb.cost = 150;

			g_pDefaultTowers[i].tb.barrelSize = 8;
			g_pDefaultTowers[i].tb.length = 35;
			g_pDefaultTowers[i].tb.point = Point2f{ g_pDefaultTowers[i].destRectf.left + g_pDefaultTowers[i].destRectf.width / 2, g_pDefaultTowers[i].destRectf.bottom + g_pDefaultTowers[i].destRectf.height / 2 };
			break;
		case TowerType::minigun:
			g_pDefaultTowers[i].tb.color = Color4f{ 0.8f,0.4f,0,1 };
			g_pDefaultTowers[i].tb.radius = 75;
			g_pDefaultTowers[i].tb.attackDamage = 10;
			g_pDefaultTowers[i].tb.attackSpeed = 0.25f;
			g_pDefaultTowers[i].tb.cost = 125;

			g_pDefaultTowers[i].tb.barrelSize = 12;
			g_pDefaultTowers[i].tb.length = 25;
			g_pDefaultTowers[i].tb.point = Point2f{ g_pDefaultTowers[i].destRectf.left + g_pDefaultTowers[i].destRectf.width / 2, g_pDefaultTowers[i].destRectf.bottom + g_pDefaultTowers[i].destRectf.height / 2 };
		default:
			// Missing "Texture" color
			g_pDefaultTowers[i].tb.color = Color4f{ 243 / 255.0f, 62 / 255.0f, 241 /255.0f,1 };
			
			g_pDefaultTowers[i].tb.radius = 100;

			g_pDefaultTowers[i].tb.barrelSize = 10;
			g_pDefaultTowers[i].tb.length = 25;
			g_pDefaultTowers[i].tb.point = Point2f{ g_pDefaultTowers[i].destRectf.left + g_pDefaultTowers[i].destRectf.width / 2, g_pDefaultTowers[i].destRectf.bottom + g_pDefaultTowers[i].destRectf.height / 2 };
			break;
		}
	}

	for (int i{0}; i < g_WorldTileAmount; ++i)
	{
		g_pBoughtTowers[i] = g_pDefaultTowers[0];
		g_pBoughtTowers[i].destRectf.left = g_pWorldTiles[i].destRectf.left + g_pBoughtTowers[i].destRectf.width * 0.2f;
		g_pBoughtTowers[i].destRectf.bottom = g_pWorldTiles[i].destRectf.bottom + g_pBoughtTowers[i].destRectf.height * 0.2f;
		g_pBought[i] = false;
	}
}
void DeleteTurrets()
{
	for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
	{
		DeleteTexture(g_pDefaultTowers[i].baseTexture);
	}
	for (int i{ 0 }; i < g_WorldTileAmount; ++i)
	{
		DeleteTexture(g_pBoughtTowers[i].baseTexture);
	}
	delete[] g_pDefaultTowers;
	g_pDefaultTowers = nullptr;
	delete[] g_pBoughtTowers;
	g_pBoughtTowers = nullptr;
	delete[] g_pBought;
	g_pBought = nullptr;
}
void DrawTurretBarrel(const TowerBarrel& tb)
{
	Point2f p2{tb.point.x + tb.length*cosf(tb.angle),tb.point.y + tb.length*sinf(tb.angle) };
	SetColor(tb.color);
	DrawLine(tb.point, p2, tb.barrelSize);
	FillEllipse(tb.point, tb.barrelSize / 2, tb.barrelSize / 2);
}
void UpdateTurretBarrel(Tower& t, const Point2f& enemyP)
{
	t.tb.point = Point2f{ t.destRectf.left + t.destRectf.width / 2, t.destRectf.bottom + t.destRectf.height / 2 };
	t.tb.angle = atan2f(t.tb.point.y - enemyP.y,t.tb.point.x - enemyP.x) - g_Pi;
}
void UpdateTurretBarrel(Tower& t, float elapsedSec)
{
	const float rotationSpeed{2};
	t.tb.point = Point2f{ t.destRectf.left + t.destRectf.width / 2, t.destRectf.bottom + t.destRectf.height / 2 };
	t.tb.angle += elapsedSec * rotationSpeed;
	if (t.tb.angle >= 2 * g_Pi) t.tb.angle -= 2 * g_Pi;
}
void UpdateTurretBarrel(Tower& t)
{
	t.tb.point = Point2f{ t.destRectf.left + t.destRectf.width / 2, t.destRectf.bottom + t.destRectf.height / 2 };
	t.tb.angle = 0;
}
void DrawTurret(const Tower& t)
{
	DrawTexture(t.baseTexture, t.destRectf, t.srcRectf);
	DrawTurretBarrel(t.tb);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void InitBuyMenu()
{
	const float scale{ g_BuyMenuButtonScale };
#pragma region InitTextures
	std::string path{};
	bool success{};

	path = "Resources/UI/yellow_checkmark.png";
	success = TextureFromFile(path, g_CheckmarkTexture);
	if (g_ShowInitMsgs) {
		if (success) std::cout << "Successfully loaded " << path << "\n";
		else std::cout << "Failed to load " << path << "\n";
	}

	path = "Resources/UI/yellow_cross.png";
	success = TextureFromFile(path, g_CrossTexture);
	if (g_ShowInitMsgs) {
		if (success) std::cout << "Successfully loaded " << path << "\n";
		else std::cout << "Failed to load " << path << "\n";
	}

	path = "Resources/UI/yellow_sliderLeft.png";
	success = TextureFromFile(path, g_SliderLeftTexture);
	if (g_ShowInitMsgs) {
		if (success) std::cout << "Successfully loaded " << path << "\n";
		else std::cout << "Failed to load " << path << "\n";
	}

	path = "Resources/UI/yellow_sliderRight.png";
	success = TextureFromFile(path, g_SliderRightTexture);
	if (g_ShowInitMsgs) {
		if (success) std::cout << "Successfully loaded " << path << "\n";
		else std::cout << "Failed to load " << path << "\n";
	}

	g_PlayButton.texture = g_CheckmarkTexture;
	g_OpenButton.texture = g_SliderLeftTexture;
#pragma endregion InitTextures
#pragma region InitUI
	const Point2f playPos{ Point2f{g_BuyMenuRectf.left + g_BuyMenuRectf.width / 2, g_BuyMenuRectf.bottom + 100} };
	Point2f openPos{g_BuyMenuRectf.left, g_BuyMenuRectf.height * 0.8f };
	if (g_IsBuyMenuActive)
	{
		openPos.x = g_BuyMenuRectf.left;
		g_OpenButton.texture = g_SliderRightTexture;
		InitUI(g_OpenButton, scale, openPos);
	}
	else 
	{
		openPos.x = g_BuyMenuRectf.left + g_BuyMenuRectf.width;
		g_OpenButton.texture = g_SliderLeftTexture;
		InitUI(g_OpenButton, scale, openPos);
	}
	InitUI(g_PlayButton, scale, playPos);

	const std::string font{ "Resources/Fonts/Kenney Blocks.ttf" };
	success = TextureFromString("Start wave", font, 48, Color4f{1,1,1,1}, g_StartWaveText.texture);
	if (success && g_ShowInitMsgs) std::cout << "Successfully init " << "Start wave\n";
	else if (!success) std::cout << "Failed to init Start wave from " << path << '\n';
	InitUI(g_StartWaveText, 0.5f, Point2f{playPos.x, playPos.y + 50});
#pragma endregion InitUI
	g_pBuyMenuTowers = new Tower[g_AmountOfDefaultTowers];
	for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
	{
		const float spaceBetween{ 10 };
		g_pBuyMenuTowers[i] = g_pDefaultTowers[i];
		g_pBuyMenuTowers[i].destRectf.left = g_BuyMenuRectf.left + (g_BuyMenuRectf.width / 2) - (g_pBuyMenuTowers[i].destRectf.width / 2);
		g_pBuyMenuTowers[i].destRectf.bottom = g_BuyMenuRectf.height * 0.8f - i * g_pBuyMenuTowers[i].destRectf.height - i * spaceBetween;
	}
}
void DrawBuyMenu()
{
	if (!g_MainMenu)
	{
		if (g_IsBuyMenuActive)
		{
			SetColor(g_BuyMenuColor4f);
			FillRect(g_BuyMenuRectf);

			if (!g_IsPlayPressed)
			{
				DrawTexture(g_StartWaveText.texture, g_StartWaveText.destRectf, g_StartWaveText.srcRectf);
				DrawTexture(g_PlayButton.texture, g_PlayButton.destRectf, g_PlayButton.srcRectf);
			}
			for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
			{
				DrawTurret(g_pBuyMenuTowers[i]);
			}
			DrawPriceTextures();
		}
		DrawTexture(g_OpenButton.texture, g_OpenButton.destRectf, g_OpenButton.srcRectf);
	}

}
void UpdateBuyMenu(float elapsedSec)
{
	if (!g_MainMenu)
	{
		if (IsInsideRect(g_OpenButton.destRectf, g_MousePosLMB))
		{
			g_MousePosLMB = Point2f{ 0,0 };
			g_IsBuyMenuActive = !g_IsBuyMenuActive;
			if (g_ShowButtonMsgs) std::cout << "OPEN BUYMENU BUTTON CLICKED\n";
		}
		else if (IsInsideRect(g_PlayButton.destRectf, g_MousePosLMB) && !g_IsPlayPressed)
		{
			g_MousePosLMB = Point2f{ 0,0 };
			if (g_ShowButtonMsgs) std::cout << "PLAY BUTTON CLICKED\n";
			g_IsPlayPressed = true;
			DisplayErrorMessage("Wave started. Good luck.", 5);
			
		}
#pragma region OpenButton
		Point2f openPos{ g_BuyMenuRectf.left, g_BuyMenuRectf.height * 0.8f };
		if (g_IsBuyMenuActive)
		{
			openPos.x = g_BuyMenuRectf.left;
			g_OpenButton.texture = g_SliderRightTexture;
			InitUI(g_OpenButton, g_BuyMenuButtonScale, openPos);
		}
		else
		{
			openPos.x = g_BuyMenuRectf.left + g_BuyMenuRectf.width;
			g_OpenButton.texture = g_SliderLeftTexture;
			InitUI(g_OpenButton, g_BuyMenuButtonScale, openPos);
		}
#pragma endregion OpenButton

		for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
		{
			UpdateTurretBarrel(g_pBuyMenuTowers[i], elapsedSec);
		}
		UpdateBuy();
	}
}
void DeleteBuyMenu()
{
	DeleteTexture(g_CheckmarkTexture);
	DeleteTexture(g_CrossTexture);
	DeleteTexture(g_SliderLeftTexture);
	DeleteTexture(g_SliderRightTexture);

	DeleteTexture(g_StartWaveText.texture);
	DeleteTexture(g_PlayButton.texture);
	DeleteTexture(g_OpenButton.texture);
}

void UpdateBuy()
{
	if (g_IsBuyMenuActive)
	{
		for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
		{
			if (IsInsideRect(g_pBuyMenuTowers[i].destRectf, g_MousePosLMB))
			{
				g_BuyTowerDisplay = g_pDefaultTowers[i];
				g_IsBuyTowerDisplay = true;
				g_MousePosLMB = Point2f{ 0,0 };
			}
		}
		if (!g_MousePosLMBClicking)
		{
			if (g_IsBuyTowerDisplay)
			{
				if (!IsInsideRect(g_BuyMenuRectf, g_CurrentMousePos))
				{
					g_BuyPos = g_CurrentMousePos;
					if (!(g_pWorldTiles[GetTile(g_BuyPos)].tile == TileType::dirt))
					{
						if (g_Player.coins >= g_BuyTowerDisplay.tb.cost)
						{
							BuyTower(g_BuyPos, g_BuyTowerDisplay);
							g_Player.coins -= g_BuyTowerDisplay.tb.cost;
							DisplayErrorMessage(".",1);
						}
						else
						{
							std::cout << "Insufficient money. You have: " << g_Player.coins 
									  << " and need " << g_BuyTowerDisplay.tb.cost 
									  << ". You need " << (g_BuyTowerDisplay.tb.cost - g_Player.coins) 
									  << " more.\n";
							const std::string msg{"Insufficient money."};
							DisplayErrorMessage(msg, 10);
						}
					}
				}
			}
			g_IsBuyTowerDisplay = false;
		}
		if (g_IsBuyTowerDisplay)
		{
			g_BuyTowerDisplay.destRectf.left = g_CurrentMousePos.x - g_BuyTowerDisplay.destRectf.width / 2;
			g_BuyTowerDisplay.destRectf.bottom = g_CurrentMousePos.y - g_BuyTowerDisplay.destRectf.height / 2;
			UpdateTurretBarrel(g_BuyTowerDisplay);
		}
	}
}
void BuyTower(const Point2f& pos, const Tower& boughtTower)
{
	const int tile{ GetTile(pos) };
	g_pBought[tile] = true;
	g_pBoughtTowers[tile].tb = boughtTower.tb;
	UpdateTurretBarrel(g_pBoughtTowers[tile]);
}
void DrawBoughtTowers()
{
	for (int i{ 0 }; i < g_WorldTileAmount; ++i)
	{
		if (g_pBought[i])
		{
			DrawTurret(g_pBoughtTowers[i]);
		}
	}
}
void UpdateBoughtTowers(float elapsedSec)
{
	if (g_WaveController.waveActive)
	{
		for (int i{ 0 }; i < g_WorldTileAmount; ++i)
		{
			if (g_pBought[i])
			{
				for (int j{ 0 }; j < g_WaveController.waveSize; ++j)
				{
					if (g_WaveController.enemies[j].isAlive)
					{
						if (GetDistance(g_pBoughtTowers[i].tb.point, g_WaveController.enemies[j].position ) <= g_pBoughtTowers[i].tb.radius)
						{
							ShootTower(g_pBoughtTowers[i], g_WaveController.enemies[j], elapsedSec);
						}
					}
				}
				if (g_pBoughtTowers[i].tb.timeSinceLastAttack <= g_pBoughtTowers[i].tb.timeSinceLastAttack)
				{
					g_pBoughtTowers[i].tb.timeSinceLastAttack += elapsedSec;
				}
			}
		}
	}
}
void ShootTower(Tower& t, Enemy& e, float elapsedSec)
{
	if (t.tb.attackSpeed <= t.tb.timeSinceLastAttack)
	{
		//std::cout << "Shot after: " << t.tb.timeSinceLastAttack << '\n';
		g_Player.coins += e.TakeDamage(t.tb.attackDamage);
		t.tb.timeSinceLastAttack -= t.tb.timeSinceLastAttack;
		UpdateTurretBarrel(t, e.position);
	}
}
void ResetBoughtTowers()
{
	for (int i{ 0 }; i < g_WorldTileAmount; ++i)
	{
		g_pBought[i] = false;
	}
}

void DisplayWaveNr()
{
	if (!g_MainMenu)
	{
		const std::string waveNrStr{ std::to_string(g_WaveController.waveNr) };
		const unsigned int waveNrStrLen{ waveNrStr.length() };
		Texture* waveDisplay{ nullptr };
		waveDisplay = new Texture[waveNrStrLen];
		for (unsigned int i{ 0 }; i < waveNrStrLen; ++i)
		{
			waveDisplay[i] = g_pNumberTextures[ASCIINumToInt(int(waveNrStr[i]))];
			const Point2f bl{ 0, g_WindowHeight - waveDisplay[i].height - 10 };
			DrawTexture(waveDisplay[i], Point2f{ bl.x + i * (waveDisplay[i].width / 2), bl.y });
		}
		delete[] waveDisplay;
		waveDisplay = nullptr;
		UserInterface waveNr{};
		const std::string font{ "Resources/Fonts/Kenney Blocks.ttf" };
		TextureFromString("Wave number:", font, 36, Color4f{ 1,1,1,1 }, waveNr.texture);
		InitUI(waveNr, 0.5f, Point2f{ 6 + waveNr.texture.width / 4, g_WindowHeight - 15 });
		DrawTexture(waveNr.texture, waveNr.destRectf, waveNr.srcRectf);
		DeleteTexture(waveNr.texture);
	}
}
void DisplayMoney()
{
	if (!g_MainMenu)
	{
		const std::string coinStr{ std::to_string(g_Player.coins) };
		const unsigned int coinStrLen{ coinStr.length() };
		Texture* moneyDisplay{ nullptr };
		moneyDisplay = new Texture[coinStrLen];
		for (unsigned int i{ 0 }; i < coinStrLen; ++i)
		{
			moneyDisplay[i] = g_pNumberTextures[ASCIINumToInt(int(coinStr[i]))];
			const Point2f bl{ g_WindowHeight,g_WindowHeight - moneyDisplay[i].height};
			DrawTexture(moneyDisplay[i], Point2f{ bl.x + i * (moneyDisplay[i].width / 2), bl.y });
			if (i == coinStrLen - 1) DrawTexture(g_pTileTextures[287], Point2f{ bl.x + (i + 1) * (moneyDisplay[i].width / 2), bl.y });
		}
		delete[] moneyDisplay;
		moneyDisplay = nullptr;
	}
}
int ASCIINumToInt(int ascii)
{
	if (ascii >= 48 && ascii <= 57)
	{
		return (ascii - 48);
	}
	else
	{
		std::cout << "WRONG ASCII VALUE: " << ascii << '\n';
		return -1;
	}
}

void DisplayErrorMessage(const std::string& msg, float secondsDisplayed)
{
	g_ErrorElapsedTime = 0;
	g_ErrorTime = secondsDisplayed;
	bool succes{};
	const std::string path{ "Resources/Fonts/Kenney Blocks.ttf" };
	succes = TextureFromString(msg, path, 40, Color4f{ 1,1,1,1 }, g_ErrorMessage.texture);
	if (succes && g_ShowInitMsgs) std::cout << "Succesfully init " << msg << " from " << path << '\n';
	else if (!succes) std::cout << "Failed to load " << msg << " from " << path << '\n';
	InitUI(g_ErrorMessage, 0.5f, Point2f{g_ErrorMessage.texture.width / 4, g_ErrorMessage.texture.width / 4});
}
void DrawErrorMessage()
{
	if (g_ErrorElapsedTime <= g_ErrorTime)
	{
		DrawTexture(g_ErrorMessage.texture, g_ErrorMessage.destRectf, g_ErrorMessage.srcRectf);
	}
}

void DrawPriceTextures()
{
	// Looking back, this should've been in 2 parts, one initialising, one drawing.
	const float scale{ 0.5f };
	const float yOffset{ 4 };
	const std::string font{ "Resources/Fonts/Kenney Blocks.ttf" };
	const Color4f priceCol{ 1,1,1,1 };
	const int priceSize{ 34 };
	bool success{ false };
	UserInterface* pDefaultTowerPriceUI{ nullptr };
	pDefaultTowerPriceUI = new UserInterface[g_AmountOfDefaultTowers]{};
	for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
	{
		const std::string priceStr{ std::to_string(g_pDefaultTowers[i].tb.cost) };
		const unsigned int priceStrLen{ priceStr.length() };
		success = TextureFromString(priceStr, font, priceSize, priceCol, pDefaultTowerPriceUI[i].texture);
		if (success && g_ShowInitMsgs) std::cout << "Succesfully init '" << priceStr << "'\n";
		else if (!success) std::cout << "Failed to load '" << priceStr << "' in font " << font << " in size " << priceSize << '\n';

		InitUI(pDefaultTowerPriceUI[i], scale, Point2f{ g_pBuyMenuTowers[i].destRectf.left + g_pBuyMenuTowers[i].destRectf.width / 2, g_pBuyMenuTowers[i].destRectf.bottom - yOffset });
		DrawTexture(pDefaultTowerPriceUI[i].texture, pDefaultTowerPriceUI[i].destRectf, pDefaultTowerPriceUI[i].srcRectf);
	}
	for (int i{ 0 }; i < g_AmountOfDefaultTowers; ++i)
	{
		DeleteTexture(pDefaultTowerPriceUI[i].texture);
	}
	delete[] pDefaultTowerPriceUI;
	pDefaultTowerPriceUI = nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void StartRei()
{
	InitTurrets();
	InitBuyMenu();
}
void DrawRei()
{
	if (g_IsBuyTowerDisplay)
	{
		DrawTurret(g_BuyTowerDisplay);
	}
	if (g_ShowGrid)
	{
		SetColor(0, 0, 1, 0.5f);
		FillEllipse(g_BuyPos, 10, 10);
		for (int i{ 0 }; i < g_WorldTileAmount; ++i)
		{
			if (g_pBought[i])
			{
				SetColor(1, 0, 0, 0.5f);
				FillEllipse(g_pBoughtTowers[i].tb.point, g_pBoughtTowers[i].tb.radius, g_pBoughtTowers[i].tb.radius);
			}
		}
		for (int i{ 0 }; i < g_WaveController.waveSize; ++i)
		{
			if (g_WaveController.enemies[i].isAlive)
			{
				SetColor(1, 1, 0.5f, 0.25f);
				FillEllipse(g_WaveController.enemies[i].position, 30, 30);
			}
		}
	}
	DrawBoughtTowers();
	DisplayMoney();
	DisplayWaveNr();
	DrawErrorMessage();

	DrawBuyMenu();
}
void UpdateRei(float elapsedSec)
{
	UpdateBuyMenu(elapsedSec);
	UpdateBoughtTowers(elapsedSec);

	g_ErrorElapsedTime += elapsedSec;
}
void EndRei()
{
	DeleteTurrets();
	DeleteBuyMenu();

	DeleteTexture(g_ErrorMessage.texture);
}