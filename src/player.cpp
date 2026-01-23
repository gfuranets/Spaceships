#include <SFML/Graphics.hpp>

#include "player.h"
#include "ship.h"

Player::Player(sf::Texture& texture, sf::RenderWindow& window, float X, float Y) :
	Ship(texture, window, X, Y), direction(sf::degrees(0.f)), hp(100)
{
	
};

void Player::move(sf::Time dt)
{
	float dirRads = direction.asRadians(), t = dt.asSeconds();
	sf::Vector2f dir({ std::cos(dirRads), std::sin(dirRads) });
	ship.move({ dir * vel * t });
}