#include "Enemy.h"


Enemy::Enemy()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

// Constructor and destructor
Enemy::Enemy(float posX, float posY)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

	this->enemySprite.setPosition(posX, posY);
}

Enemy::~Enemy()
{

}

// Accessors
const sf::FloatRect Enemy::getBounds() 
{
	return this->enemySprite.getGlobalBounds();
}

const sf::Vector2f& Enemy::getPosition() 
{
	return this->enemySprite.getPosition();
}

const int& Enemy::getHp() 
{
	return this->hp;
}

const int& Enemy::getPoints() 
{
	return this->points;
}

const int& Enemy::getDamage() 
{
	return this->damage;
}

void Enemy::setPosition(const sf::Vector2f pos)
{
	this->enemySprite.setPosition(pos);
}

void Enemy::setPosition(const float x, const float y)
{
	this->enemySprite.setPosition(x, y);
}

// Modifiers
void Enemy::resetHp()
{
	this->hp = hpMax;
}

void Enemy::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

// Public functions
void Enemy::Update()
{
	this->Move();
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(this->enemySprite);
}

void Enemy::Move()
{
	this->enemySprite.move(this->direction.x, this->speed);

}

// Private functions
void Enemy::initVariables()
{
	this->speed  = 1.f;	
	this->hpMax  = 10;
	this->hp     = hpMax;
	this->damage = 5;
	this->points = 5;
	this->direction.x = 0.f;
	this->direction.y = 0.f;

}

void Enemy::initTexture()
{
	// Load a texture from a file 
	if (!this->texture.loadFromFile("../textures/Enemy.png"))
	{
		std::cout << "ERROR::ENEMY::INITTEXTURE: Could not load texture file." << std::endl;
	}
}

void Enemy::initSprite()
{
	//Set the texture to the sprite
	this->enemySprite.setTexture(this->texture);
}
