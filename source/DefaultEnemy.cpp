#include "DefaultEnemy.h"

DefaultEnemy::DefaultEnemy() 
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}

DefaultEnemy::DefaultEnemy(float posX, float posY)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

	this->enemySprite.setPosition(posX, posY);
}

DefaultEnemy::~DefaultEnemy()
{

}

void DefaultEnemy::initVariables()
{
	this->speed = 1.f;
	this->hpMax = 10;
	this->hp = hpMax;
	this->damage = 5;
	this->points = 3;
	this->direction.x = 0.f;
	this->direction.y = 0.f;
	this->spawnRate = 50;
}

void DefaultEnemy::initTexture()
{
	// Load a texture from a file 
	if (!this->texture.loadFromFile("../textures/DefaultEnemy.png"))
	{
		std::cout << "ERROR::DEFAULTENEMY::INITTEXTURE: Could not load texture file." << std::endl;
	}
}

void DefaultEnemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->texture);

	// Resize the sprite  
	this->enemySprite.scale(0.4f, 0.4f);
}
