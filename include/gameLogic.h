#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFMl/Graphics.hpp>
#include <vector>

#include "enemy.h"
#include "bullet.h"
#include "player.h"

void enemyUpdate(sf::RenderWindow& window, sf::Time dt, Player& player, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture);
void bulletUpdate(sf::RenderWindow& window, sf::Time dt, std::vector<std::unique_ptr<Bullet>>& bullets);
void drawEntities(sf::RenderWindow& window, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet>>& enemyBullets);

#endif