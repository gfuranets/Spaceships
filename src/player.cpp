#include <SFML/Graphics.hpp>

#include "player.h"
#include "ship.h"

Player::Player(sf::Texture& texture, sf::RenderWindow& window, float X, float Y) :
	Ship(texture, window, X, Y)
{

};