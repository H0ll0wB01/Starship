
#include "FastEnemy.h"

FastEnemy::FastEnemy()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}

FastEnemy::FastEnemy(float posX, float posY)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

	this->enemySprite.setPosition(posX, posY);
}

FastEnemy::~FastEnemy()
{
}

void FastEnemy::initVariables()
{
	this->speed = 1.4f;
	this->hpMax = 5;
	this->hp = hpMax;
	this->damage = 5;
	this->points = 15;
	this->direction.x = -10.f;
	this->direction.y = 0.f;
	this->spawnRate = 35;
}

void FastEnemy::initTexture()
{
	// Load a texture from a file 
	if (!this->texture.loadFromFile("../textures/FastEnemy.png"))
	{
		std::cout << "ERROR::FASTENEMY::INITTEXTURE: Could not load texture file." << std::endl;
	}
}

void FastEnemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->texture);

	sf::IntRect rect(0, 0, 180, 300);
	this->enemySprite.setTextureRect(rect);
	// Resize the sprite  
	this->enemySprite.scale(0.3f, 0.3f);
}

void FastEnemy::Move()
{
	this->enemySprite.move(this->direction.x, this->speed);

	// If collisions width left  bounds
	if (this->getBounds().left < 0.f)
	{
		this->setPosition(-4.f, this->getBounds().top);
		// change direction
		this->direction.x =10;
	}

	// If collisions width right  bounds
	else if (this->getBounds().left + this->getBounds().width >= 800)
	{
		this->setPosition(800 - this->getBounds().width, this->getBounds().top);
		// change direction
		this->direction.x = -10;

	}
}

void FastEnemy::Update()
{
	this->Move();
}


