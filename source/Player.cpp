#include "Player.h"

// Constructor and destructor

Player::Player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}

Player::~Player()
{

}

// Accessors

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

const int& Player::getCooldawn() const
{
	return this->attackCooldown;
}

// Modifiers
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setCooldown(int newCooldawn)
{
	switch (newCooldawn)
	{
		case 1:
			shot01 = true;
			shot02 = false;
			shot03 = false;
 			break;
		case 2:
			shot01 = false;
			shot02 = true;
			shot03 = false;
			break;
		case 3: 
			shot01 = false;
			shot02 = false;
			shot03 = true;
			break;
		;
	}
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

// Public functions

void Player::Update()
{
	this->UpdateCooldown();
}


void Player::UpdateCooldown()
{
	if (this->attackCooldown < this->attackCooldownMax) 
	{
		if (shot01 == true) 
		{
			attackCooldown += 0.5f;
		}
		
		if (shot02 == true) 
		{
			attackCooldown += 0.15f;
		}
		
		if (shot03 == true) 
		{
			attackCooldown += 0.09f; 
		}
	}
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::MovePlayer(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}


// Private functions

void Player::initTexture()
{
	// Load a texture from a file 
	if (!this->texture.loadFromFile("../textures/ship.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE: Could not load texture file." << std::endl;
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize the sprite  
	this->sprite.scale(0.7f, 0.7f);

}

void Player::initVariables()
{
	this->movementSpeed = 4.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	this->sprite.setPosition(400.f, 500.f);	

	this->newCooldawn = 0.5f;
	this->hpMax = 50;
	this->hp = this->hpMax;
}
