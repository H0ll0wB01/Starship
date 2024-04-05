#ifndef BULLET_H
#define BULLET_H


#include "Player.h"

class Bullet
{
	public:	
		// Constructor and destructor
		Bullet(sf::Texture* texture);
		Bullet(sf::Texture* texture,float posX,float posY, float dirX, float dirY, float bullet_Speed);
		Bullet(sf::Texture* texture,float posX,float posY, float dirX, float dirY, float rotation, float bullet_Speed);
		virtual ~Bullet();


		// Accessor
		const sf::FloatRect getBounds() const ;
		const int& getDamage() const;

		// Public functions 
		void Update();
		void Render(sf::RenderTarget* target);
		void Shot(float posX, float posY, float dirX, float dirY, float rotation, float bulletSpeed, int damage);
	
private:

		// Visual stuffs
		sf::Sprite bulletSprite;

		// Private variables 
		sf::Vector2f bulletDirection;
		float bulletSpeed; 
		int bulletDamage;
};

#endif // !BULLET_H
