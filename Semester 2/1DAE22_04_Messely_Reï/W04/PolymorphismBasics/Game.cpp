#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"

Game::Game()
{

}
Game::~Game()
{
	for (GameObject* ptr : m_pGameObjects)
	{
		delete ptr;
	}
	m_pGameObjects.clear();
}

void Game::AddEnemy()
{
	m_pGameObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	m_pGameObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	m_pGameObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };

	std::cout << "--> All Game objects\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}
}

void Game::ReportEnemies() const
{
	std::cout << "--> Enemies\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		Enemy* pEnem = dynamic_cast<Enemy*>(ptr);
		if (pEnem != nullptr) std::cout  << pEnem->ToString() << "\n";
	}
	std::cout << "--> Enemies\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		if (typeid(*ptr) == typeid(Enemy)) std::cout << ptr->ToString() << "\n";
	}
}