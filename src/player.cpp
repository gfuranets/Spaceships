#include <SFML/Graphics.hpp>

#include "player.h"
#include "ship.h"

Player::Player(sf::RenderWindow& window, sf::Texture& playerTexture, float X, float Y) :
	Ship(window, playerTexture, X, Y), direction(sf::degrees(0.f)), hp(100)
{
	
};

void Player::move(sf::Time dt)
{
	float dirRads = direction.asRadians(), t = dt.asSeconds();
	sf::Vector2f dir({ std::cos(dirRads), std::sin(dirRads) });
	ship.move({ dir * vel * t });
}