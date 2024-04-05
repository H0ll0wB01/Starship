#include "TankEnemy.h"

TankEnemy::TankEnemy()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}

TankEnemy::TankEnemy(float posX, float posY)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

	this->enemySprite.setPosition(posX, posY);
}

TankEnemy::~TankEnemy()
{
	
}

void TankEnemy::initVariables()
{
	this->speed = 0.1f;
	this->hpMax = 100;
	this->hp = hpMax;
	this->damage = 100;
	this->points = 100;
	this->direction.x = 0.f;
	this->direction.y = 0.f;
	this->spawnRate = 15;
}

void TankEnemy::initTexture()
{
	// Load a texture from a file 
	if (!this->texture.loadFromFile("../textures/TankEnemy.png"))
	{
		std::cout << "ERROR::TANKTENEMY::INITTEXTURE: Could not load texture file." << std::endl;
	}
	
}

void TankEnemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->texture);
	sf::IntRect rect(0.f,0.f, 520,520);
	this->enemySprite.setTextureRect(rect);
	this->enemySprite.setScale(0.5, 0.5);
}
