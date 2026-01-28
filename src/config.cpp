#include "config.h"

namespace GameConfig
{
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 900;

	extern const float PLAYER_VELOCITY = 300.f;
	extern const float ENEMY_VELOCITY = 150.f;
	extern const sf::Angle PLAYER_ANGULAR_VEL = sf::degrees(180.f);
	extern const sf::Angle ENEMY_ANGULAR_VEL = sf::degrees(25.f);

	const float PLAYER_BULLET_VELOCITY = 500.f;
	const float ENEMY_BULLET_VELOCITY = 300.f;

	const sf::Time PLAYER_TIME_COOLDOWN = sf::seconds(0.1f);
	const sf::Time ENEMY_TIME_COOLDOWN = sf::seconds(0.5f);

}
