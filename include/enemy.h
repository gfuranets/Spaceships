#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "ship.h"

class Enemy : public Ship {
public:
	bool collided;

	explicit Enemy(sf::Texture& texture, sf::RenderWindow& window, float X, float Y);

	void bulletCollision(std::vector<Bullet*>& bullets);
};

#endif
