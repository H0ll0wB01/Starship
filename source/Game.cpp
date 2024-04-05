
#include "Game.h"

// Constructors and destructors 
Game::Game() 
{
	this->initWindow();
	this->initTextures();
	this->initSystems();
	this->initWorld();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	// Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	// Delete Player Bullets
	for (auto *i :this->PActBullets)
	{
		delete i;
	}
	for (auto *i :this->PInactBullets)
	{
		delete i;
	}

	// Delete all enemies
	for (auto* i : this->ActDefEnemyPool)
	{
		delete i;
	}
	for (auto* i : this->InactDefEnemyPool)
	{
		delete i;
	}
	for (auto* i : this->ActFastEnemyPool)
	{
		delete i;
	}
	for (auto* i : this->InactFastEnemyPool)
	{
		delete i;
	}for (auto* i : this->ActTankEnemyPool)
	{
		delete i;
	}
	for (auto* i : this->InactTankEnemyPool)
	{
		delete i;
	}
}

// Public Functions
void Game::Run()
{
	while (this->window->isOpen())
	{
		this->UpdatePoolEvents();

		if (this->player->getHp() > 0) 
		{
			this->Update();
			this->Render();
		}
	}

}

void Game::Update()
{
	// All updates here
		
	this->UpdateInput();

	this->player->Update();

	this->UpdateCollisions();
	
	this->UpdateBullets();

	this->UpdateBombs();
	
	this->UpdateEnemies();
	
	this->UpdateCombat();

	this->UpdateGUI();

}

void Game::Render()
{
	this->window->clear();

	// Draw world
	this->RenderWorld();
	
	// Render player
	this->player->Render(*this->window);
	
	// Render the Player bullets
	for (auto* bullet : this->PActBullets)
	{
		bullet->Render(this->window);
	}

	// Render the Player bombs
	for (auto* bomb: this->PActbombs)
	{
		bomb->Render(this->window);
	}

	// Render enemies
	for (auto* enemy : this->ActDefEnemyPool)
	{
		enemy->Render(this->window);
	}
	for (auto* enemy : this->ActFastEnemyPool)
	{
		enemy->Render(this->window);
	}
	for (auto* enemy : this->ActTankEnemyPool)
	{
		enemy->Render(this->window);
	}

	// Draw GUI 
	this->RenderGUI();

	// Game Over screen	
	if (this->player->getHp() <= 0) 
	{
		this->window->draw(this->gameOverText);
	}

	this->window->display();

}

void Game::UpdatePoolEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}


void Game::UpdateInput()
{
	// Move player 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->MovePlayer(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->MovePlayer(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->MovePlayer(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->MovePlayer(0.f, -1.f);

	// Shot player

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		switch (shootIndex)
		{
			case 1:
				this->Shot01();
				break;
			case 2:
				this->Shot02();
				break;
			case 3:
				this->Shot03();
				break;
			default:
				this->Shot01();
				break;
		}
	}

	// Change type shoot if it is possible
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		this->shootIndex = 1;
		this->player->setCooldown(1);
		

		this->playerShotType01.setFillColor(sf::Color::Red);
		this->playerShotType02.setFillColor(sf::Color(51,47,46,250));
		this->playerShotType03.setFillColor(sf::Color(51, 47, 46, 250));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && this->points >=50) // AUMENTAR EN UN FUTURO
	{
		this->shootIndex = 2;
		this->player->setCooldown(2);

		this->playerShotType02.setFillColor(sf::Color::Red);
		this->playerShotType01.setFillColor(sf::Color(51, 47, 46, 250));
		this->playerShotType03.setFillColor(sf::Color(51, 47, 46, 250));

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && this->points >= 100) // AUMENTAR EN UN FUTURO
	{
		this->shootIndex = 3;
		this->player->setCooldown(3);

		this->playerShotType03.setFillColor(sf::Color::Red);
		this->playerShotType02.setFillColor(sf::Color(51, 47, 46, 250));
		this->playerShotType01.setFillColor(sf::Color(51, 47, 46, 250));
	}
}


	

void Game::UpdateCollisions()
{
	// Left world player collision
	if (this->player->getBounds().left < 0.f) 
	{
		this->player->setPosition(-4.f, this->player->getBounds().top);
	}

	// Right world player collision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	
	// Top world player collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	
	// Buttom world player collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition( this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

	
}

void Game::UpdateBullets()
{
	unsigned bulletCounter = 0;

	for (auto* bullet : this->PActBullets)	
	{
		bullet->Update();
		
		// Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) 
		{ 
			this->PActBullets.erase(this->PActBullets.begin() + bulletCounter);
			this->PInactBullets.push_back(bullet);
			
			--bulletCounter;
		}
		++bulletCounter;
	}
}

void Game::UpdateBombs()
{
	unsigned bombCounter = 0;

	for (auto* bomb : this->PActbombs)
	{
		bomb->Update();

		// Bomb culling (top of screen)
		if (bomb->getBounds().top + bomb->getBounds().height < 0.f)
		{
			// Delete Pbomb
			this->PActbombs.erase(this->PActbombs.begin() + bombCounter);
			this->PInactbombs.push_back(bomb);
			bomb->resetBomb();
			--bombCounter;
			
		}
		++bombCounter;
	}
	
}

void Game::UpdateEnemies()
{
	// Controls the timer to spawn a enemy
	this->spawnTimer += 1.f;
	
	int randomNum = rand() % 100 + 1;
	
	// Enemy Spawn Controller

	if (randomNum <= 50) // Default enemy spawn
	{
		if (this->spawnTimer >= this->spawnTimerMax && this->InactDefEnemyPool.size() > 0)
		{
			auto* newEnemy = InactDefEnemyPool.back();

			InactDefEnemyPool.pop_back();

			newEnemy->setPosition(rand() % -600, -100);

			ActDefEnemyPool.push_back(newEnemy);

			this->spawnTimer = 0.f;
		}

	}

	if (randomNum <= 90) // Fast enemy spawn
	{
		if (this->spawnTimer >= this->spawnTimerMax && this->InactFastEnemyPool.size() > 0)
		{
			auto* newEnemy = InactFastEnemyPool.back();

			InactFastEnemyPool.pop_back();

			newEnemy->setPosition(rand() % -600, -100);

			ActFastEnemyPool.push_back(newEnemy);

			this->spawnTimer = 0.f;

		}
	}

	if (randomNum <= 100) // Tank enemy spawn
	{
		if (this->spawnTimer >= this->spawnTimerMax && this->InactTankEnemyPool.size() > 0)
		{
			auto* newEnemy = InactTankEnemyPool.back();

			InactTankEnemyPool.pop_back();

			newEnemy->setPosition(rand() % -600, -100);

			ActTankEnemyPool.push_back(newEnemy);

			this->spawnTimer = 0.f;

		}
	}
	
	this->UpdateDefEnemies();

	this->UpdateFastEnemies();

	this->UpdateTankEnemies();
}

void Game::UpdateDefEnemies()
{
	// Default enemy update
	for (auto* enemy : this->ActDefEnemyPool)
	{
		unsigned enemyCounter = 0;
		enemy->Update();

		// Enemy culling (Buttom of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{

			this->player->loseHp(this->ActDefEnemyPool.at(enemyCounter)->getDamage() / 2.f);

			this->ActDefEnemyPool.erase(this->ActDefEnemyPool.begin() + enemyCounter);
			this->InactDefEnemyPool.push_back(enemy);
		}

		// Enemy hit the player 
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->ActDefEnemyPool.at(enemyCounter)->getDamage());

			this->ActDefEnemyPool.erase(this->ActDefEnemyPool.begin() + enemyCounter);
			this->InactDefEnemyPool.push_back(enemy);
		}
		++enemyCounter;

		// Right world enemy collision
		if (enemy->getBounds().left + enemy->getBounds().width >= this->window->getSize().x)
		{
			enemy->setPosition(this->window->getSize().x - enemy->getBounds().width, enemy->getBounds().top);
		}
	}
}

void Game::UpdateFastEnemies()
{
	// Fast enemy update
	for (auto* enemy : this->ActFastEnemyPool)
	{
		unsigned enemyCounter = 0;
		enemy->Update();

		// Enemy culling (Buttom of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{

			this->player->loseHp(this->ActFastEnemyPool.at(enemyCounter)->getDamage() / 2.f);

			this->ActFastEnemyPool.erase(this->ActFastEnemyPool.begin() + enemyCounter);
			this->InactFastEnemyPool.push_back(enemy);
		}

		// Enemy hit the player 
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->ActFastEnemyPool.at(enemyCounter)->getDamage());

			this->ActFastEnemyPool.erase(this->ActFastEnemyPool.begin() + enemyCounter);
			this->InactFastEnemyPool.push_back(enemy);
		}
		++enemyCounter;
	}
}

void Game::UpdateTankEnemies()
{
	// Tank enemy update
	for (auto* enemy : this->ActTankEnemyPool)
	{
		unsigned enemyCounter = 0;
		enemy->Update();

		// Enemy culling (Buttom of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{

			this->player->loseHp(this->ActTankEnemyPool.at(enemyCounter)->getDamage() / 2.f);

			this->ActTankEnemyPool.erase(this->ActTankEnemyPool.begin() + enemyCounter);
			this->InactTankEnemyPool.push_back(enemy);
		}

		// Enemy hit the player 
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->ActTankEnemyPool.at(enemyCounter)->getDamage());

			this->ActTankEnemyPool.erase(this->ActTankEnemyPool.begin() + enemyCounter);
			this->InactTankEnemyPool.push_back(enemy);
		}
		++enemyCounter;

		// Right world enemy collision
		if (enemy->getBounds().left + enemy->getBounds().width >= this->window->getSize().x)
		{
			enemy->setPosition(this->window->getSize().x - enemy->getBounds().width, enemy->getBounds().top);
		}
	}
}

void Game::UpdateCombat()
{
	// Updates Combat enemies
	this->UpdateCombatDefEnemies();
	this->UpdateCombatFastEnemies();
	this->UpdateCombatTankEnemies();
}

void Game::UpdateCombatDefEnemies()
{
	// Default enemy Update Combat
	for (int i = 0; i < this->ActDefEnemyPool.size(); i++)
	{
		bool enemyDeleted = false;

		for (size_t k = 0; k < PActBullets.size() && enemyDeleted == false; k++)
		{
			// If enemy is hit by a bullet 
			if (this->ActDefEnemyPool[i]->getBounds().intersects(this->PActBullets[k]->getBounds()))
			{
				this->ActDefEnemyPool[i]->loseHp(this->PActBullets.at(k)->getDamage());

				if (this->ActDefEnemyPool[i]->getHp() <= 0)
				{
					// take the enemy out of ActDefEnemyPool and puts in inactEnemyPool and reset the enemy 
					auto* newEnemy = this->ActDefEnemyPool[i];
					this->InactDefEnemyPool.emplace_back(newEnemy);
					newEnemy->resetHp();

					// Obtain points
					this->points += this->ActDefEnemyPool[i]->getPoints();

					// Erase the enemy
					this->ActDefEnemyPool.erase(this->ActDefEnemyPool.begin() + i);
					enemyDeleted = true;
				}

				// take the Bullet out of PActBullets and puts in PInActBullets
				Bullet* newBullet = this->PActBullets[k];

				this->PInactBullets.emplace_back(newBullet);

				this->PActBullets.erase(this->PActBullets.begin() + k);
			}
		}

		// If is hit by a Bomb 
		for (size_t k = 0; k < PActbombs.size() && enemyDeleted == false; k++)
		{
			if (this->ActDefEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				this->PActbombs[k]->bombExplode();

				
			}

			// Bomb dissapear when the time is over butt when explosion is active make damage to enemies
			if (this->ActDefEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				// take the Bomb out of PActBombs and puts in PInActBombs
				this->ActDefEnemyPool[i]->loseHp(this->PActbombs.at(k)->getDamage());

				if (this->ActDefEnemyPool[i]->getHp() <= 0)
				{
					// Obtain points
					this->points += this->ActDefEnemyPool[i]->getPoints();

					this->ActDefEnemyPool.erase(this->ActDefEnemyPool.begin() + i);
					enemyDeleted = true;
				}

				if (this->PActbombs[k]->getTimeToDisapear() >= 5.f)
				{
					Bomb* newBomb = this->PActbombs[k];

					this->PInactbombs.emplace_back(newBomb);
					
					this->PActbombs.erase(this->PActbombs.begin() + k);
					
					newBomb->resetBomb();
				}
			}
		}
	}

}

void Game::UpdateCombatFastEnemies()
{
	// Fast enemy Update Combat
	for (int i = 0; i < this->ActFastEnemyPool.size(); i++)
	{
		bool enemyDeleted = false;

		for (size_t k = 0; k < PActBullets.size() && enemyDeleted == false; k++)
		{
			// If enemy is hit by a bullet 
			if (this->ActFastEnemyPool[i]->getBounds().intersects(this->PActBullets[k]->getBounds()))
			{
				this->ActFastEnemyPool[i]->loseHp(this->PActBullets.at(k)->getDamage());

				if (this->ActFastEnemyPool[i]->getHp() <= 0)
				{
					// take the enemy out of ActEnemyPool and puts in inactEnemyPool and reset the enemy 
					auto* newEnemy = this->ActFastEnemyPool[i];
					this->InactFastEnemyPool.emplace_back(newEnemy);
					newEnemy->resetHp();

					// Obtain points
					this->points += this->ActFastEnemyPool[i]->getPoints();

					// Erase the enemy
					this->ActFastEnemyPool.erase(this->ActFastEnemyPool.begin() + i);
					enemyDeleted = true;
				}

				// take the Bullet out of PActBullets and puts in PInActBullets
				Bullet* newBullet = this->PActBullets[k];

				this->PInactBullets.emplace_back(newBullet);

				this->PActBullets.erase(this->PActBullets.begin() + k);
			}
		}


		// If is hit by a Bomb 
		for (size_t k = 0; k < PActbombs.size() && enemyDeleted == false; k++)
		{
			if (this->ActFastEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				this->PActbombs[k]->bombExplode();
			}

			// Bomb dissapear when the time is over butt when explosion is active make damage to enemies
			if (this->ActFastEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				this->ActFastEnemyPool[i]->loseHp(this->PActbombs.at(k)->getDamage());
				// take the Bomb out of PActBombs and puts in PInActBombs

				if (this->PActbombs[k]->getTimeToDisapear() >= 5.f) 
				{
					Bomb* newBomb = this->PActbombs[k];


					this->PInactbombs.emplace_back(newBomb);

					this->PActbombs.erase(this->PActbombs.begin() + k);
					
					newBomb->resetBomb();
				}


				if (this->ActFastEnemyPool[i]->getHp() <= 0)
				{
					// Obtain points
					this->points += this->ActFastEnemyPool[i]->getPoints();

					this->ActFastEnemyPool.erase(this->ActFastEnemyPool.begin() + i);
					enemyDeleted = true;

				}
				
			}
		}
	}

}

void Game::UpdateCombatTankEnemies()
{
	// Tank enemy Update Combat
	for (int i = 0; i < this->ActTankEnemyPool.size(); i++)
	{
		bool enemyDeleted = false;

		for (size_t k = 0; k < PActBullets.size() && enemyDeleted == false; k++)
		{
			// If enemy is hit by a bullet 
			if (this->ActTankEnemyPool[i]->getBounds().intersects(this->PActBullets[k]->getBounds()))
			{
				this->ActTankEnemyPool[i]->loseHp(this->PActBullets.at(k)->getDamage());

				if (this->ActTankEnemyPool[i]->getHp() <= 0)
				{
					// take the enemy out of ActEnemyPool and puts in inactEnemyPool and reset the enemy 
					auto* newEnemy = this->ActTankEnemyPool[i];
					this->InactTankEnemyPool.emplace_back(newEnemy);
					newEnemy->resetHp();

					// Obtain points
					this->points += this->ActTankEnemyPool[i]->getPoints();

					// Erase the enemy
					this->ActTankEnemyPool.erase(this->ActTankEnemyPool.begin() + i);
					enemyDeleted = true;
				}

				// take the Bullet out of PActBullets and puts in PInActBullets
				Bullet* newBullet = this->PActBullets[k];

				this->PInactBullets.emplace_back(newBullet);

				this->PActBullets.erase(this->PActBullets.begin() + k);
			}
		}

		// If is hit by a Bomb 
		for (size_t k = 0; k < PActbombs.size() && enemyDeleted == false; k++)
		{
			if (this->ActTankEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				this->PActbombs[k]->bombExplode();

			}

			// Bomb dissapear when the time is over butt when explosion is active make damage to enemies
			if (this->ActTankEnemyPool[i]->getBounds().intersects(this->PActbombs[k]->getBounds()))
			{
				this->ActTankEnemyPool[i]->loseHp(this->PActbombs.at(k)->getDamage());
				// take the Bomb out of PActBombs and puts in PInActBombs

				if (this->PActbombs[k]->getTimeToDisapear() >= 5.f)
				{
					Bomb* newBomb = this->PActbombs[k];

					this->PInactbombs.emplace_back(newBomb);

					this->PActbombs.erase(this->PActbombs.begin() + k);
					
					newBomb->resetBomb();
				}

				if (this->ActTankEnemyPool[i]->getHp() <= 0)
				{
					// Obtain points
					this->points += this->ActTankEnemyPool[i]->getPoints();

					this->ActTankEnemyPool.erase(this->ActTankEnemyPool.begin() + i);
					enemyDeleted = true;

				}

			}
		}
	}
}

void Game::UpdateGUI()
{
	// Update score
	std::stringstream ss;
	ss << "SCORE: " << this->points;
	this->pointsTexts.setString(ss.str());

	// Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(305.f * hpPercent, this->playerHpBar.getSize().y));

}

void Game::RenderGUI()
{
	// All GUI stuffs render here 
	this->window->draw(this->pointsTexts);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->playerShotType01);
	this->window->draw(this->playerShotType02);
	this->window->draw(this->playerShotType03);
}

void Game::RenderWorld()
{
	// draw the world sprite 
	this->window->draw(this->worldSprite);
}

void Game::Shot01()
{
	// One bullet with a rapid fire rate
	Bullet* newBullet = PInactBullets.back();
	PInactBullets.pop_back();
	PActBullets.push_back(newBullet);
	newBullet->Shot(this->player->getPos().x
		+ this->player->getBounds().width / 2.5f, this->player->getPos().y, 0.f, -1.f, 0.f, 5.f, 5);
}

void Game::Shot02()
{
	// Three bullets more slowly 
	
	// first bullet
	Bullet* newBullet = PInactBullets.back();
	PInactBullets.pop_back();
	PActBullets.push_back(newBullet);
	newBullet->Shot(this->player->getPos().x
		+ this->player->getBounds().width / 2.5f, this->player->getPos().y, 0.f, -1.f, 0.f, 5.f, 5);
	
	// second bullet
	Bullet* newBullet02 = PInactBullets.back();
	PInactBullets.pop_back();
	PActBullets.push_back(newBullet02);
	newBullet02->Shot(this->player->getPos().x
		+ this->player->getBounds().width / 2.5f, this->player->getPos().y, 0.5f, -1.f, 20.f, 5.f, 5);

	// third bullet
	Bullet* newBullet03 = PInactBullets.back();
	PInactBullets.pop_back();
	PActBullets.push_back(newBullet03);
	newBullet03->Shot(this->player->getPos().x
		+ this->player->getBounds().width / 2.5f, this->player->getPos().y, -0.5f, -1.f, -20.f, 5.f, 5);
}

void Game::Shot03()
{
	// Shoots the bomb 

	Bomb* newBomb = PInactbombs.back();
	PInactbombs.pop_back();
	PActbombs.push_back(newBomb);
	newBomb->Shot(this->player->getPos().x
		+ this->player->getBounds().width / 2.5f, this->player->getPos().y, 0.f, -1.f, 0.f, 5.f, 50);

}

// Private functions

void Game::initWindow()
{
	// Initialice the window at 800 x 600
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Starship", sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	this->window->setFramerateLimit(100);
}

void Game::initTextures()
{
	// Bullet textures
	this->textures["BULLET"] = new sf::Texture;
	this->textures["BULLET"]->loadFromFile("../textures/Pbullet.png");
}

void Game::initGUI()
{
	// Load Font 
	if (!this->gameFont.loadFromFile("../fonts/gameFont.ttf"))
		std::cout << "ERROR::GAME::INIGUI: Failed to load font." << "\n";

	// Init score text
	this->pointsTexts.setPosition(sf::Vector2f(700.f, 25.f));
	this->pointsTexts.setFont(this->gameFont);
	this->pointsTexts.setCharacterSize(20);
	this->pointsTexts.setFillColor(sf::Color::White);
	this->pointsTexts.setString("Score");

	// init gameOver text
	this->gameOverText.setFont(this->gameFont);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition
	(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width/2.f,
	this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// init Player GUI

	// Hp bar
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 560.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	// shot type 01 square 
	this->playerShotType01.setSize(sf::Vector2f(25.f, 25.f));
	this->playerShotType01.setFillColor(sf::Color::Red);
	this->playerShotType01.setPosition(sf::Vector2f(750.f, 550.f));

	// shot type 02 square 
	this->playerShotType02.setSize(sf::Vector2f(25.f, 25.f));
	this->playerShotType02.setFillColor(sf::Color(51, 47, 46, 250));
	this->playerShotType02.setPosition(sf::Vector2f(750.f, 500.f));

	// shot type 03 square 
	this->playerShotType03.setSize(sf::Vector2f(25.f, 25.f));
	this->playerShotType03.setFillColor(sf::Color(51, 47, 46, 250));
	this->playerShotType03.setPosition(sf::Vector2f(750.f, 450.f));
}

void Game::initWorld()
{
	// texture from the background
	if (!this->worldTexture.loadFromFile("../textures/Background.png"))
		std::cout << "ERROR::GAME::INIWORLD: Could not load texture file." << "\n";

	this->worldSprite.setTexture(this->worldTexture);
}

void Game::initSystems()
{
	this->points = 0;
	this->shootIndex = 1;
	
	// Inactive enemy pool with 20 DefaultEnemies
	for (int i = 0; i < 20; i++) 
	{
		InactDefEnemyPool.push_back(new DefaultEnemy());
	}
	
	// Inactive enemy pool with 20 FastEnemies
	for (int i = 0; i < 10; i++) 
	{
		InactFastEnemyPool.push_back(new FastEnemy());
	}
	
	// Inactive enemy pool with 5 DefaultEnemies
	for (int i = 0; i < 5; i++) 
	{
		InactTankEnemyPool.push_back(new TankEnemy());
	}
	
	// Inactive bullets pool with 50 Bullets
	for (int i = 0; i < 50; i++) 
	{
		PInactBullets.push_back(new Bullet(this->textures["BULLET"]));
	}
	
	// Inactive bombs pool with 5 Bombs
	for (int i = 0; i < 50; i++) 
	{
		PInactbombs.push_back(new Bomb());
	}
	
}

void Game::initPlayer()
{
	this->player = new Player(); 
	this->player->setCooldown(1);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 100.f;
	this->spawnTimer = spawnTimerMax;
}
