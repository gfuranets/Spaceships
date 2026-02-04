#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "ship.h"
#include "config.h"
#include "game.h"

// forward declaration
class Player;
class Bullet;

class Enemy : public Ship 
{
public:
	bool collided;

	explicit Enemy(sf::RenderWindow& window, sf::Texture& texture, float X, float Y, sf::Time timeCoolDown);

	void move(sf::Time dt) override;
	void bulletCollision(std::vector<std::unique_ptr<Bullet>>& playerBullets, Game& game);
	void getPlayerOrientation(sf::RenderWindow& window, Player& player, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture);
	void update(sf::RenderWindow& window, sf::Time dt, Player& player, std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture, Game& game);
};

#endif
