#ifndef BOMB_H
#define BOMB_H

#include "Player.h"

class Bomb
{
	public:
		// Constructor and destructor
		Bomb();
		Bomb(float posX, float posY, float dirX, float dirY, float bomb_speed);
		virtual ~Bomb();
		
		// Accessor
		const sf::FloatRect getBounds() const;
		const int& getDamage() const;
		const float& getTimeToDisapear() const;

		// Public functions 
		void Update();
		void Render(sf::RenderTarget* target);
		void setPos(const sf::Vector2f pos);
		void bombExplode();
		bool CheckIfExplode();
		void Shot(float posX, float posY, float dirX, float dirY, float rotation, float bulletSpeed, int damage);
		void resetBomb();
		
	private:
	
		// Visual stuffs
		sf::Sprite bombSprite;
		sf::Texture explTexture;
		sf::Texture bombTexture;


		// Private variables 
		sf::Vector2f bombDirection;
		float bombSpeed;
		int bombDamage;
		bool bombExploded;
		float timeToDissapear;
		
		// Private Functions
		void initTextures();
		void initVariables();
		void UpdateTimeToDissapear();

};

#endif // !BOMB_H
