#pragma once

// SFML
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Others include 
#include <iostream>

class Player
{
	public:
		
		// Constructor and destructor
		Player();
		virtual ~Player();

		// Accessor
		const sf::Vector2f& getPos() const;
		const sf::FloatRect getBounds() const;
		const int& getHp() const;
		const int& getHpMax() const;
		const int& getCooldawn() const;

		// Modifiers
		void setPosition(const sf::Vector2f pos);
		void setPosition(const float x, const float y);
		void setCooldown(int newCooldawn);
		void setHp(const int hp);
		void loseHp(const int value);


		// Public functions
		void Update();
		void UpdateCooldown();
		void Render(sf::RenderTarget& target);
		void MovePlayer(const float dirX, const float dirY);
		const bool canAttack();


	private:

		// Visual stuffs
		sf::Sprite sprite;
		sf::Texture texture;
		
		// Private variables
		float movementSpeed;
		float attackCooldown;
		float attackCooldownMax;
		float newCooldawn;

		int hp;
		int hpMax;
		
		bool shot01;
		bool shot02;
		bool shot03;

		// Private funcitions
		void initTexture();
		void initSprite();
		void initVariables();
};

