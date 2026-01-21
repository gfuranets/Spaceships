#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "ship.h"
#include "player.h"

class Enemy : public Ship {
public:
	bool collided;

	explicit Enemy(sf::Texture& texture, sf::RenderWindow& window, float X, float Y);

	void bulletCollision(std::vector<std::unique_ptr<Bullet>>& bullets);
	void trackPlayer(Player& player);
};

#endif
