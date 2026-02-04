#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "player.h"

class Game
{
public:
	int score, level, enemyCount, maxEnemyCount;
	sf::RectangleShape container, healthBar;
	sf::Text scoreText, enemyCountText;

	Game(sf::Font& font);

	void draw(sf::RenderWindow& window);
	void update(Player& player, unsigned int currentEnemyCount);
};

#endif