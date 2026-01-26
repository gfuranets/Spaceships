#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "ship.h"

class Player : public Ship 
{
public:
	int hp;
	sf::Angle direction;

	explicit Player(sf::RenderWindow& window, sf::Texture& texture, float X, float Y);

	void move(sf::Time dt) override;
};

#endif