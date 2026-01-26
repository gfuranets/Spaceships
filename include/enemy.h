#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "ship.h"
#include "player.h"

class Enemy : public Ship 
{
public:
	bool collided;

	explicit Enemy(sf::RenderWindow& window, sf::Texture& texture, float X, float Y);

	void move(sf::Time dt) override;
	void bulletCollision(std::vector<std::unique_ptr<Bullet>>& playerBullets);
	void getPlayerOrientation(sf::RenderWindow& window, Player& player, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture);
	void update(sf::RenderWindow& window, sf::Time dt, Player& player, std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture);
};

#endif
