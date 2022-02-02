#pragma once

//TODO
// 
//

struct Player
{
	bool isAlive{ true };
	float health{};
	float maxHealth{};
	int coins{};
	Point2f position{};

	void TakeDamage(float damage)
	{
		health -= damage;
		if (health <= 0)
		{
			health = 0;
			isAlive = false;
		}
	}
};

struct EnemySprite
{
	Texture texture;
	int currentFrame;
	int cols{4};
	float scale{ 1.f };
};

struct Enemy
{
	EnemySprite sprite{  };
	float maxHealth{};
	float health{};
	float speed{};
	float attack{};
	int reward{};
	Direction direction;
	Point2f position{};
	bool isAlive{false};
	//bool isRemoved{ false };

	int TakeDamage(float damage)
	{
		health -= damage;
		if (health <= 0)
		{
			health = 0;
			isAlive = false;
			return reward;
		}
		return 0;
	}

	void Draw()
	{
		switch (direction)
		{
		case Direction::up:
		case Direction::start:
			sprite.currentFrame = 1;
			break;
		case Direction::down:
			sprite.currentFrame = 3;
			break;
		case Direction::right:
			sprite.currentFrame = 0;
			break;
		case Direction::left:
			sprite.currentFrame = 2;
			break;
		}

		Rectf srcRect{};
		srcRect.width = sprite.texture.width / sprite.cols;
		srcRect.height = sprite.texture.height;
		srcRect.left = sprite.currentFrame * srcRect.width;
		srcRect.bottom = srcRect.height;

		Rectf destRect{};		
		destRect.width = srcRect.width * sprite.scale;
		destRect.height = srcRect.height * sprite.scale;
		destRect.left = position.x - destRect.width / 2;
		destRect.bottom = position.y - destRect.height / 2;

		DrawTexture(sprite.texture, destRect, srcRect);
		SetColor(1.f, 0.f, 0.f);
		const float healthLeft{ health / maxHealth };
		FillRect(destRect.left + destRect.width / 4, destRect.bottom + destRect.height * 0.75f, (destRect.width / 2) * healthLeft, 10);
		SetColor(0.5f, 0.5f, 0.5f);
		DrawRect(destRect.left + destRect.width / 4, destRect.bottom + destRect.height * 0.75f, destRect.width / 2, 10);
	}
};

struct EnemyTemplate
{
	Enemy enemy{};
	int minWave{};
	float healthModifier{1.f};
	float weightedOccurance{};
};

struct EnemyController
{
	Point2f startPos{};
	//int nrEnemies{}
	int waveSize{}, waveProgress{}, waveNr{}, nrEnemiesAlive{};
	Enemy* enemies{ nullptr };
	float timeInterval{}, elapsedTime{ }, waveSizeModifier{1.f};
	bool waveActive{ false };
};

Player g_Player{};
EnemyController g_WaveController{};
const float g_CellWidth{ g_WindowWidth / g_WorldTileAmountCol};
const int g_EnemyTemplateAmount{ 6 };
EnemyTemplate* g_pEnemyTemplates{nullptr};
int g_WaveSize{10};
bool g_IsWaveFinished{false};

void StartJonathan();
void DrawJonathan();
void UpdateJonathan(float elapsedSec);
void EndJonathan();

void CreateEnemyPath(int x, int y);
void CreatePath(int& x, int& y, int length, const Direction dir, int* pPathGrid, const bool addBorder = true, const TileType tile = TileType::dirt);
void InitWaveController(int gridX, int gridY);
void InitPlayer(float health = 100.f, int coins = 200);
void InitEnemyTemplates();
void InitEnemySprite(Texture& texture, const std::string& path);


bool IsSafeIndex(int idx, int nrCols, int nrRows);
bool IsSafeIndex(int idx, int amountOfTiles);
bool IsSafeIndex(int x, int y, int nrCols, int nrRows);
bool IsTileOccupied(int* pPathGrid, int x, int y, int nrCols, int nrRows);
void PlaceBorderTile(int x, int y, int* pPathGrid);
Point2f GetPositionFromTile(int x, int y);
Point2f GetPositionFromTile(float x, float y);
Point2f GetTileFromIndex(int idx, int nrCols);

void UpdateWaveController(float elapsedSec);
void UpdateEnemies(float elapsedSec);
Enemy CreateEnemyFromTemplate(const Enemy& enemyTemplate, int wave, const Point2f& position, const Direction dir);
void BuildWaveTemplate(int* pTemplateIdx, int size, int wave);
void BuildWave(int* pTemplateIdx, int size, int wave);
void StartWave(int& amountOfEnemies, float timeInterval = 1.f);

void DrawEnemies();
void DrawPlayer();

void DeleteEnemyTemplates();
void ResetWaveController();

void StartJonathan()
{
	int gridX{ 3 }, gridY{ 0 };
	CreateEnemyPath(gridX, gridY);
	InitPlayer(100.f, 200);
	InitEnemyTemplates();
	InitWaveController(gridX, gridY);
}
void DrawJonathan()
{
	DrawEnemies();
}
void UpdateJonathan(float elapsedSec)
{
	UpdateWaveController(elapsedSec);
}
void EndJonathan()
{
	DeleteEnemyTemplates();
}

void CreateEnemyPath(int x, int y)
{
	int* pPathGrid{ new int[g_WorldTileAmount] {} };
	//Direction prevDir{ Direction::start };
	CreatePath(x, y, 9, Direction::start, pPathGrid);
	CreatePath(x, y, 5, Direction::right, pPathGrid);
	CreatePath(x, y, 8, Direction::down, pPathGrid);
	CreatePath(x, y, 10, Direction::right, pPathGrid);
	CreatePath(x, y, 4, Direction::up, pPathGrid);
	CreatePath(x, y, 18, Direction::left, pPathGrid);
	CreatePath(x, y, 1, Direction::end, pPathGrid, false, TileType::pathEnd);
	g_Player.position = GetPositionFromTile(x, y);
	delete[] pPathGrid;
	pPathGrid = nullptr;
}

void InitPlayer(float health, int coins)
{
	g_Player.health = health;
	g_Player.maxHealth = health;
	g_Player.coins = coins;
	g_Player.isAlive = true;
}

void InitEnemyTemplates()
{
	g_pEnemyTemplates = new EnemyTemplate[g_EnemyTemplateAmount];
	int idx{};
	//brown pilot template
	g_pEnemyTemplates[idx].minWave = 1;
	g_pEnemyTemplates[idx].weightedOccurance = 1.f;

	Enemy brownPilot{};
	std::string path{ "Resources/Rotated/brownPilot.png" };
	InitEnemySprite(brownPilot.sprite.texture, path);
	brownPilot.attack = 10.f;
	brownPilot.maxHealth = 100.f;
	brownPilot.reward = 20;
	brownPilot.speed = 50.f;
	g_pEnemyTemplates[idx].enemy = brownPilot;
	++idx;

	//green pilot template
	g_pEnemyTemplates[idx].minWave = 3;
	g_pEnemyTemplates[idx].weightedOccurance = 0.75f;

	Enemy greenPilot{};
	path = "Resources/Rotated/greenPilot.png" ;
	InitEnemySprite(greenPilot.sprite.texture, path);
	greenPilot.attack = 15.f;
	greenPilot.maxHealth = 200.f;
	greenPilot.reward = 35;
	greenPilot.speed = 55.f;
	g_pEnemyTemplates[idx].enemy = greenPilot;
	++idx;

	//grey pilot template
	g_pEnemyTemplates[idx].minWave = 5;
	g_pEnemyTemplates[idx].weightedOccurance = 0.5f;

	Enemy greyPilot{};
	path = "Resources/Rotated/greyPilot.png";
	InitEnemySprite(greyPilot.sprite.texture, path);
	greyPilot.attack = 20.f;
	greyPilot.maxHealth = 300.f;
	greyPilot.reward = 50;
	greyPilot.speed = 60.f;
	g_pEnemyTemplates[idx].enemy = greyPilot;
	++idx;

	//elite pilot template
	g_pEnemyTemplates[idx].minWave = 7;
	g_pEnemyTemplates[idx].weightedOccurance = 0.25f;

	Enemy elitePilot{};
	path = "Resources/Rotated/elitePilot.png";
	InitEnemySprite(elitePilot.sprite.texture, path);
	elitePilot.attack = 25.f;
	elitePilot.maxHealth = 400.f;
	elitePilot.reward = 75;
	elitePilot.speed = 70.f;
	g_pEnemyTemplates[idx].enemy = elitePilot;
	++idx;

	//green plane template
	g_pEnemyTemplates[idx].minWave = 9;
	g_pEnemyTemplates[idx].weightedOccurance = 0.1f;

	Enemy greenPlane{};
	path = "Resources/Rotated/greenPlane.png";
	InitEnemySprite(greenPlane.sprite.texture, path);
	greenPlane.attack = 50.f;
	greenPlane.maxHealth = 750.f;
	greenPlane.reward = 100;
	greenPlane.speed = 60.f;
	g_pEnemyTemplates[idx].enemy = greenPlane;
	++idx;

	//green plane template
	g_pEnemyTemplates[idx].minWave = 11;
	g_pEnemyTemplates[idx].weightedOccurance = 0.05f;

	Enemy greyPlane{};
	path = "Resources/Rotated/greyPlane.png";
	InitEnemySprite(greyPlane.sprite.texture, path);
	greyPlane.attack = 75.f;
	greyPlane.maxHealth = 1500.f;
	greyPlane.reward = 150;
	greyPlane.speed = 55.f;
	g_pEnemyTemplates[idx].enemy = greyPlane;
	++idx;
}

void InitEnemySprite(Texture& texture, const std::string& path)
{
	bool success{};
	success = TextureFromFile(path, texture);
	if (g_ShowInitMsgs) if (success) std::cout << "Successfully loaded " << path << "\n";
	if (!success)
	{
		std::cout << "Failed to load " << path << "\n";
	}
}

void DeleteEnemyTemplates()
{
	for (int i{}; i < g_EnemyTemplateAmount; ++i)
	{
		DeleteTexture(g_pEnemyTemplates[i].enemy.sprite.texture);
	}
	
	delete[] g_pEnemyTemplates;
	g_pEnemyTemplates = nullptr;	
}

bool IsSafeIndex(int x, int y, int nrCols, int nrRows)
{

	return x >= 0 && y >= 0 && IsSafeIndex(GetIndex(y, x, nrCols), nrCols * nrRows);
}

bool IsSafeIndex(int idx, int nrCols, int nrRows)
{
	
	return IsSafeIndex(idx, nrCols * nrRows);
}

bool IsSafeIndex(int idx, int amountOfTiles)
{

	return idx >= 0 && idx < (amountOfTiles);
}

bool IsTileOccupied(int* pPathGrid, int x, int y, int nrCols, int nrRows)
{
	int idx{ GetIndex(y, x, nrCols) };
	if (IsSafeIndex(idx, nrCols, nrRows))
	{
		return pPathGrid[idx] == 1;
	}
	return false;
}

void CreatePath(int& x, int& y, int length, const Direction dir, int* pPathGrid, const bool addBorder, const TileType tile)
{
	int dummy{};
	int* pDir = &dummy;
	int displacement{ };
	int counter{ length };

	//assign x or y to the pointer, depending on the direction state
	switch (dir)
	{
	case Direction::right:
	{
		pDir = &x;
		displacement = 1;
	}
	break;
	case Direction::left:
	{
		pDir = &x;
		displacement = -1;
	}
	break;
	case Direction::up:
	case Direction::start:
	{
		pDir = &y;
		displacement = 1;
	}
	break;
	case Direction::down:
	{
		pDir = &y;
		displacement = -1;
	}
	break;
	default:
	break;
	}
	
	int idx{ GetIndex(y, x, g_WorldTileAmountCol) };
	if (!IsSafeIndex(idx, g_WorldTileAmountCol, g_WorldTileAmountRow))
	{
		return;
	}

	g_pWorldTiles[idx].direction = dir;
	//add path tiles along the requested indices
	while(counter > 0)
	{		
		
		g_pWorldTiles[idx].texture = g_pTileTextures[int(tile)];
		g_pWorldTiles[idx].tile = TileType::dirt;
		pPathGrid[idx] = 1;
		
		if (addBorder)
		{
			PlaceBorderTile(x - 1, y, pPathGrid);
			PlaceBorderTile(x + 1, y, pPathGrid);
			PlaceBorderTile(x, y - 1, pPathGrid);
			PlaceBorderTile(x, y + 1, pPathGrid);
			PlaceBorderTile(x - 1, y - 1, pPathGrid);
			PlaceBorderTile(x - 1, y + 1, pPathGrid);
			PlaceBorderTile(x + 1, y + 1, pPathGrid);
			PlaceBorderTile(x + 1, y - 1, pPathGrid);
		}
		*pDir += displacement;
		--counter;
		idx = GetIndex(y, x, g_WorldTileAmountCol);
		if (!IsSafeIndex(idx, g_WorldTileAmountCol, g_WorldTileAmountRow))
		{
			return;
		}
	}
}

void PlaceBorderTile(int x, int y, int* pPathGrid)
{
	const int amountOfTiles{ g_WorldTileAmountCol * g_WorldTileAmountRow };
	int idx{ GetIndex(y, x, g_WorldTileAmountCol) };
	if (!IsSafeIndex(idx, amountOfTiles))
	{
		return;
	}
	else if (pPathGrid[idx] == 1)
	{
		return;
	}
	int borderValue{};
	/* bordervalues:
	*  32 2 64
	*  1  E 4
	*  16 8 128
	*/
	borderValue |= IsTileOccupied(pPathGrid, x - 1, y, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 1 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x, y + 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 2 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x + 1, y, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 4 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x, y - 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 8 : 0;

	borderValue |= IsTileOccupied(pPathGrid, x - 1, y - 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 16 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x - 1, y + 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 32 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x + 1, y + 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 64 : 0;
	borderValue |= IsTileOccupied(pPathGrid, x + 1, y - 1, g_WorldTileAmountCol, g_WorldTileAmountRow) ? 128 : 0;
	
	TileType tile{};
	switch (borderValue)
	{
	case 1:
	case 17:
	case 33:
	case 49:
		//middle right border
		tile = TileType::borderMiddleRight; // 94;
		break;
	case 4:
	case 68:
	case 132:
	case 196:
		//middle left border
		tile = TileType::borderMiddleLeft;
		break;
	case 2:
	case 34:
	case 66:
	case 98:
		//middle top border
		tile = TileType::borderMiddleTop; 
		break;
	case 8:
	case 24:
	case 136:
	case 152:
		//middle bottom border
		tile = TileType::borderMiddleBottom; 
		break;
	case 16:
		//bottomleft open
		tile = TileType::borderBottomLeftOutside; 
		break;
	case 32:
		//topleft open
		tile = TileType::borderTopLeftOutside; 
		break;
	case 64:
		//topright open
		tile = TileType::borderTopRightOutside; 
		break;
	case 128:
		//bottomright open		
		tile = TileType::borderBottomRightOutside;
		break;
	case 25: 
	case 57:
	case 153:
	case 185:
		//bottomleft closed
		tile = TileType::borderBottomLeftInside;
		break;
	case 35:
	case 51:
	case 99:
	case 115:
		//topleft closed
		tile = TileType::borderTopLeftInside;
		
		break;
	case 70:
	case 102:
	case 198:
	case 230:
		//topright closed
		tile = TileType::borderTopRightInside;
		break;
	case 140:
	case 156:
	case 204:
	case 220:
		//bottomright closed
		tile = TileType::borderBottomRightInside;
		break;
	default:
		return;
	}

	g_pWorldTiles[idx].texture = g_pTileTextures[int(tile)];
	g_pWorldTiles[idx].tile = tile;
}


void UpdateWaveController(float elapsedSec)
{
	if (g_WaveController.waveActive)
	{
		g_WaveController.elapsedTime += elapsedSec;
		if (g_IsWaveFinished)
		{

			ResetWaveController();
			return;
		}
		else if (g_WaveController.elapsedTime > g_WaveController.timeInterval) {
			if (g_WaveController.waveProgress < g_WaveController.waveSize - 1)
			{			
				++g_WaveController.waveProgress;
				g_WaveController.enemies[g_WaveController.waveProgress].isAlive = true;
				
			}			
			g_WaveController.elapsedTime -= g_WaveController.timeInterval;
		}
		UpdateEnemies(elapsedSec);
		
	}
	else if (g_IsPlayPressed) {
		g_IsPlayPressed = false;
		StartWave(g_WaveSize);		
	}
	
	
}

void UpdateEnemies(float elapsedSec)
{
	g_WaveController.nrEnemiesAlive = 0;
	for (int i{ 0 }; i <= g_WaveController.waveProgress; ++i)
	{
		
		if (g_WaveController.enemies[i].isAlive)
		{
			++g_WaveController.nrEnemiesAlive;
			switch (g_WaveController.enemies[i].direction)
			{
			case Direction::right:
			{
				g_WaveController.enemies[i].position.x += g_WaveController.enemies[i].speed * elapsedSec;
			}
			break;
			case Direction::left:
			{
				g_WaveController.enemies[i].position.x += -g_WaveController.enemies[i].speed * elapsedSec;
			}
			break;
			case Direction::up:
			case Direction::start:
			{
				g_WaveController.enemies[i].position.y += g_WaveController.enemies[i].speed * elapsedSec;
			}
			break;
			case Direction::down:
			{
				g_WaveController.enemies[i].position.y += -g_WaveController.enemies[i].speed * elapsedSec;
			}
			break;
			}

			const int idx{ GetTile(g_WaveController.enemies[i].position) };
			Point2f gridPosition{ GetTileFromIndex(idx, g_WorldTileAmountCol) };
			Point2f tileMiddlePoint{ GetPositionFromTile(gridPosition.x, gridPosition.y) };

			if (GetDistance(tileMiddlePoint, g_WaveController.enemies[i].position) < 1.f)
			{
				Direction dir = g_pWorldTiles[GetIndex(int(gridPosition.y), int(gridPosition.x), g_WorldTileAmountCol)].direction;
				if (dir == Direction::end)
				{
					//Damage the player
					g_Player.TakeDamage(g_WaveController.enemies[i].attack);
					g_WaveController.enemies[i].isAlive = false;
					if (!g_Player.isAlive)
					{
						ResetWaveController();
						g_IsGameOver = true;
						return;
					}
				}
				else if (dir != Direction::none)
				{
					g_WaveController.enemies[i].direction = dir;
					switch (g_WaveController.enemies[i].direction)
					{
					case Direction::right:
					case Direction::left:
					{
						g_WaveController.enemies[i].position.y = tileMiddlePoint.y;
					}
					break;
					case Direction::up:
					case Direction::start:
					case Direction::down:
					{
						g_WaveController.enemies[i].position.x = tileMiddlePoint.x;
					}
					break;
					}
				}
			}
		}
	}
	if (g_WaveController.waveProgress == g_WaveController.waveSize - 1 && g_WaveController.nrEnemiesAlive == 0)
	{
		g_IsWaveFinished = true;
	}
}

void InitWaveController(int gridX, int gridY)
{
	g_WaveController.startPos = GetPositionFromTile(gridX, gridY);
	g_WaveController.waveSizeModifier = 1.2f;
}

void ResetWaveController()
{
	//g_WaveController.nrEnemies = 0;
	g_WaveController.waveProgress = 0;
	g_WaveController.waveSize = 0;
	g_WaveController.waveActive = false;
	g_WaveController.nrEnemiesAlive = 0;
	g_IsWaveFinished = false;
	
	delete[] g_WaveController.enemies;
	g_WaveController.enemies = nullptr;
	
}

void StartWave(int& amountOfEnemies, float timeInterval)
{
	if (g_WaveController.waveActive)
	{
		return;
	}
	++g_WaveController.waveNr;
	g_WaveController.timeInterval = timeInterval;
	g_WaveController.waveSize = amountOfEnemies;
	g_WaveController.waveProgress = -1;
	g_WaveController.nrEnemiesAlive = amountOfEnemies;
	g_WaveController.enemies = new Enemy[amountOfEnemies]{};
	

	int* pTemplateIndices{ new int[amountOfEnemies] {} };
	BuildWaveTemplate(pTemplateIndices, amountOfEnemies, g_WaveController.waveNr);
	BuildWave(pTemplateIndices, amountOfEnemies, g_WaveController.waveNr);
	g_WaveController.waveActive = true;
	g_WaveSize = int (g_WaveSize * g_WaveController.waveSizeModifier);
	delete[] pTemplateIndices;
	pTemplateIndices = nullptr;
}

void BuildWaveTemplate(int* pTemplateIdx, int size, int wave)
{
	float weightedTotal{};
	int lastIdx{};
	for (int i{}; i < g_EnemyTemplateAmount; ++i)
	{
		if (g_pEnemyTemplates[i].minWave <= wave)
		{
			weightedTotal += g_pEnemyTemplates[i].weightedOccurance;
			//std::cout << "enemy " << i << " registered for next wave" << std::endl;
			if (i > lastIdx)
			{
				lastIdx = i;
			}
		}
	}
	int loggedAmount{0};
	for (int i{}; i < g_EnemyTemplateAmount; ++i)
	{
		if (g_pEnemyTemplates[i].minWave <= wave)
		{
			float weightedAmount{ g_pEnemyTemplates[i].weightedOccurance / weightedTotal };
			int amount{ int(roundf(size * weightedAmount)) };
			//safeties to prevent over or underflow of array size
			if (i == lastIdx)
			{
				amount = size - loggedAmount;
			}
			if (amount < 0 || (loggedAmount + amount) > size)
			{
				return;
			}
			else if ((loggedAmount + amount) > size)
			{
				amount = 0;
				loggedAmount = size;
			}

			for (int j{ loggedAmount}; j < loggedAmount + amount; ++j)
			{
				pTemplateIdx[j] = i;
			}

			loggedAmount += amount;
		}
	}
}

void BuildWave(int* pTemplateIdx, int size, int wave)
{
	const Point2f startingPos{ g_WaveController.startPos.x, g_WaveController.startPos.y - g_CellWidth };
	for (int i{}; i < size; ++i)
	{
		const Enemy enemy = g_pEnemyTemplates[pTemplateIdx[i]].enemy;
		g_WaveController.enemies[i] = CreateEnemyFromTemplate(enemy, wave, startingPos, Direction::start);
	}
}

Enemy CreateEnemyFromTemplate(const Enemy& enemyTemplate, int wave, const Point2f& position, const Direction dir)
{
	Enemy enemy{};
	enemy.sprite = enemyTemplate.sprite;
	enemy.health = enemyTemplate.maxHealth;
	enemy.maxHealth = enemyTemplate.maxHealth;
	enemy.attack = enemyTemplate.attack;
	enemy.speed = enemyTemplate.speed;
	enemy.reward = enemyTemplate.reward;
	enemy.direction = dir;
	enemy.position = position;
	return enemy;
}

Point2f GetPositionFromTile(int x, int y)
{
	return Point2f{ g_CellWidth * x + g_CellWidth / 2, g_CellWidth * y + g_CellWidth / 2 };
}

Point2f GetPositionFromTile(float x, float y)
{
	return Point2f{ g_CellWidth * x + g_CellWidth / 2, g_CellWidth * y + g_CellWidth / 2 };
}

Point2f GetTileFromIndex(int idx, int nrCols)
{
	return Point2f{ float(idx % nrCols), float(idx / nrCols) };
}

void DrawEnemies()
{
	if (g_WaveController.waveActive)
	{
		for (int i{}; i <= g_WaveController.waveProgress; ++i)
		{
			if (g_WaveController.enemies[i].isAlive)
			{
				g_WaveController.enemies[i].Draw();
			}
		}
	}
	DrawPlayer();
}

void DrawPlayer()
{
	if (!g_MainMenu)
	{
		const float healthLeft{ g_Player.health / g_Player.maxHealth };
		SetColor(1.f, 0.f, 0.f);
		FillRect(g_Player.position.x - g_CellWidth / 3, g_Player.position.y + g_CellWidth / 1.5f, g_CellWidth * healthLeft * 2 / 3.f, 10);
		SetColor(0.5f, 0.5f, 0.5f);
		DrawRect(g_Player.position.x - g_CellWidth / 3, g_Player.position.y + g_CellWidth / 1.5f, g_CellWidth * 2 / 3.f, 10, 3.f);
	}
}