#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

namespace GameConfig
{
	// WINDOW VARIABLES
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;

	// SHIPS MOVEMENT VARIABLES
	extern const float PLAYER_VELOCITY;
	extern const float ENEMY_VELOCITY;
	extern const sf::Angle PLAYER_ANGULAR_VEL;
	extern const sf::Angle ENEMY_ANGULAR_VEL;

	// BULLET VARIABLES
	extern const float PLAYER_BULLET_VELOCITY;
	extern const float ENEMY_BULLET_VELOCITY;

	// SHOTTING VARIABLES
	extern const sf::Time PLAYER_TIME_COOLDOWN;
	extern const sf::Time ENEMY_TIME_COOLDOWN;
}

#endif
