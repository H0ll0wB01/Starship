#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
	public:
		// Constructor and destructor
		Enemy();
		Enemy(float posX, float posY);
		virtual ~Enemy();
		
		// Accessor
		const sf::FloatRect getBounds();
		const sf::Vector2f& getPosition();
		const int& getHp();
		const int& getPoints();
		const int& getDamage();


		// Modifiers
		void setPosition(const sf::Vector2f pos);
		void setPosition(const float x, const float y);

		void resetHp();
		void loseHp(const int value);

		// Public functions
		void Render(sf::RenderTarget* target);
		void virtual Update();
		void virtual Move();

	protected:
		// Enemy initialicers
		void virtual initVariables();
		void virtual initTexture();
		void virtual initSprite();

		// Visual stuffs
		sf::Sprite enemySprite;
		sf::Texture texture;
	
		// Variables
		int spawnRate;
		float speed;
		int hp;
		int hpMax;
		int damage;
		int points;
		sf::Vector2f direction;		
};

#endif // !ENEMY_H
