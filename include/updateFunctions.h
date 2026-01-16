#ifndef UPDATEFUNCTIONS_H
#define UPDATEFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy.h"
#include "bullet.h"

void handleEnemyLogic(std::vector<Enemy*>& enemies, sf::Time dt);
void handleBulletLogic(std::vector<Bullet*>& bullets, sf::RenderWindow& window, sf::Time dt);

void clearObjects(std::vector<Enemy*>& enemies, std::vector<Bullet*>& bullets);

#endif
