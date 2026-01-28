#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "ship.h"
#include "config.h"

// forward declaration
class Enemy;
class Bullet;

class Player : public Ship 
{
public:
	int hp;
	sf::Angle direction;

	explicit Player(sf::RenderWindow& window, sf::Texture& texture, float X, float Y, sf::Time timeCoolDown);

	void move(sf::Time dt) override;
	void bulletCollision(std::vector<std::unique_ptr<Bullet>>& enemyBullets);
	void enemyCollision(std::vector<std::unique_ptr<Enemy>>& enemies);
	void update(sf::RenderWindow& window, sf::Time dt, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& enemyBullets);
};

#endif