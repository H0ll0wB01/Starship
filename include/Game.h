#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#include "Player.h"
#include "Bullet.h"
#include "Bomb.h"
#include "Enemy.h"
#include "DefaultEnemy.h"
#include "TankEnemy.h"
#include "FastEnemy.h"


class Game
{
public:
	// Constructors and destructors 
	Game();
	virtual ~Game();

	// Public functions
	void Run();
	
	void Update();
	void UpdatePoolEvents();
	void UpdateInput();
	void UpdateCollisions();
	void UpdateBullets();
	void UpdateBombs();
	void UpdateEnemies();
	void UpdateDefEnemies();
	void UpdateFastEnemies();
	void UpdateTankEnemies();
	void UpdateCombat();
	void UpdateCombatDefEnemies();
	void UpdateCombatFastEnemies();
	void UpdateCombatTankEnemies();
	void UpdateGUI();

	void Render();
	void RenderGUI();
	void RenderWorld();

private:

	// Game Window
	sf::RenderWindow* window;

	// GUI
	sf::Font gameFont;
	sf::Text pointsTexts;

	sf::Text gameOverText;

	// World
	sf::Texture worldTexture;
	sf::Sprite worldSprite;

	// Systems 
	unsigned points;
	unsigned playerHp;
	
	// Proyectiles
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*>PActBullets;
	std::vector<Bullet*>PInactBullets;
	std::vector<Bomb*>PActbombs;
	std::vector<Bomb*>PInactbombs;
	

	int shootIndex;
	void Shot01();
	void Shot02();
	void Shot03();

	// Player 
	Player* player;

	// Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::RectangleShape playerShotType01;
	sf::RectangleShape playerShotType02;
	sf::RectangleShape playerShotType03;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	bool canSpawn;
	std::vector<Enemy*> ActDefEnemyPool;
	std::vector<Enemy*> InactDefEnemyPool;

	std::vector<Enemy*> ActFastEnemyPool;
	std::vector<Enemy*> InactFastEnemyPool;

	std::vector<Enemy*> ActTankEnemyPool;
	std::vector<Enemy*> InactTankEnemyPool;

	// Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initEnemies();
};