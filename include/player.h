#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "ship.h"

class Player : public Ship 
{
public:
	int hp;

	explicit Player(sf::Texture& texture, sf::RenderWindow& window, float X, float Y);


};

#endif