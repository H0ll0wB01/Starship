#include "Bomb.h"

Bomb::Bomb()
{
	this->initVariables();

	this->initTextures();

}

// Constructors and destructors
Bomb::Bomb( float posX, float posY, float dirX, float dirY, float bomb_speed)
{
	// Initialice variables
	this->bombSprite.setPosition(posX, posY);
	this->bombSprite.setScale(0.7f, 0.3f);
	this->bombDirection.x = dirX;
	this->bombDirection.y = dirY;
	this->bombSpeed = bomb_speed;
	this->bombDamage = 10;
	this->bombExploded = false;
	this->timeToDissapear = 0.f;

	initTextures();

}

Bomb::~Bomb()
{
	
}

// Public fucntions
const sf::FloatRect Bomb::getBounds() const
{
	return this->bombSprite.getGlobalBounds();
}

const int& Bomb::getDamage() const
{
	return this->bombDamage;
}

const float& Bomb::getTimeToDisapear() const
{
	return this->timeToDissapear;
}

// Public functions
void Bomb::Update()
{
	if (this->bombExploded == false)
	{
		// Bomb movement
		this->bombSprite.move(this->bombSpeed * this->bombDirection);
	}
	
	if (this->bombExploded == true)
	{
		UpdateTimeToDissapear();
	}
}

void Bomb::Render(sf::RenderTarget* target)
{
	target->draw(this->bombSprite);
}

void Bomb::setPos(const sf::Vector2f pos)
{
	this->bombSprite.setPosition(pos);
}

void Bomb::bombExplode()
{
	this->bombExploded = true;

	//Set the explosion texture to the sprite
	this->bombSprite.setTexture(this->explTexture);

	sf::Vector2f middle;
	middle.x = bombSprite.getTextureRect().width / 3.f;
	middle.y = bombSprite.getTextureRect().height / 3.f;
	bombSprite.setOrigin(middle);

	this->bombSprite.setScale(3.f, 3.f);
}

bool Bomb::CheckIfExplode()
{
	return this->bombExploded;
}
	
void Bomb::initTextures()
{
	if (!this->explTexture.loadFromFile("../textures/explBomb.png"))
	{
		std::cout << "ERROR::BOMB::INITTEXTURE: Could not load texture file." << std::endl;
	}
	
	
	if (!this->bombTexture.loadFromFile("../textures/pBomb.png"))
	{
		std::cout << "ERROR::BOMB::INITTEXTURE: Could not load texture file." << std::endl;
	}

	//Set the bomb texture to the sprite
	this->bombSprite.setTexture(this->bombTexture);
	sf::Vector2f middle;
	middle.x = bombSprite.getTextureRect().width / 2.f;
	middle.y = bombSprite.getTextureRect().height / 2.f;
	bombSprite.setOrigin(middle);
}

void Bomb::initVariables()
{
	this->bombSprite.setScale(0.7f, 0.3f);
	this->bombDirection.x = 0;
	this->bombDirection.y = -1;
	this->bombSpeed = 1.0f;
	this->bombDamage = 50;
	this->bombExploded = false;
	this->timeToDissapear = 0.f;
}

// Shoots the bomb
void Bomb::Shot(float posX, float posY, float dirX, float dirY, float rotation, float bulletSpeed, int damage)
{
		this->bombSprite.setPosition(posX, posY);
		this->bombSprite.setRotation(rotation);
		this->bombDirection.x = dirX;
		this->bombDirection.y = dirY;
		this->bombSpeed = bulletSpeed;
		this->bombDamage = damage;	
}

void Bomb::resetBomb()
{
	this->initVariables();
	this->initTextures();
}


void Bomb::UpdateTimeToDissapear()
{
	if (this->timeToDissapear < 10.f)
	{
		timeToDissapear += 0.15f;
	}
}
