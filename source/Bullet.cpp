#include "Bullet.h"


// Constructor and destructor
Bullet::Bullet(sf::Texture* texture)
{
	this->bulletSprite.setTexture(*texture);
	this->bulletDamage = 5;
	this->bulletSpeed = 0;
}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float bullet_Speed)
{
	this->bulletSprite.setTexture(*texture);
	this->bulletSprite.setPosition(posX, posY);
	this->bulletDirection.x = dirX;
	this->bulletDirection.y = dirY;
	this->bulletSpeed = bullet_Speed;
	this->bulletDamage = 5;

}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float rotation, float bullet_Speed)
{
	this->bulletSprite.setTexture(*texture);
	this->bulletSprite.setPosition(posX, posY);
	this->bulletSprite.setRotation(rotation);
	this->bulletDirection.x = dirX;
	this->bulletDirection.y = dirY;
	this->bulletSpeed = bullet_Speed;
	this->bulletDamage = 5;
}

Bullet::~Bullet()
{
	
}


const sf::FloatRect Bullet::getBounds() const
{
	return this->bulletSprite.getGlobalBounds();
}

const int& Bullet::getDamage() const
{
	return this->bulletDamage;

}

// Public functions
void Bullet::Update()
{
	// Bullet movement
	this->bulletSprite.move(this->bulletSpeed * this->bulletDirection);
}

void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(this->bulletSprite);
}

//Bullet shot
void Bullet::Shot(float posX, float posY, float dirX, float dirY, float rotation, float bulletSpeed, int damage)
{
	this->bulletSprite.setPosition(posX, posY);
	this->bulletSprite.setRotation(rotation);
	this->bulletDirection.x = dirX;
	this->bulletDirection.y = dirY;
	this->bulletSpeed = bulletSpeed;
	this->bulletDamage = damage;
}

