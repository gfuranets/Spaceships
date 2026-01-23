#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "ship.h"

class Player : public Ship 
{
public:
	int hp;
	sf::Angle direction;

	explicit Player(sf::Texture& texture, sf::RenderWindow& window, float X, float Y);

	void move(sf::Time dt) override;
};

#endif