#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#include "game.h"
#include "player.h"

Game::Game(sf::Font& font) :
	scoreText(font), enemyCountText(font), score(0), level(1), enemyCount(0), maxEnemyCount(2)
{
	scoreText.setCharacterSize(20);
	enemyCountText.setCharacterSize(20);

	scoreText.setFillColor(sf::Color::White);
	enemyCountText.setFillColor(sf::Color::White);

	container.setSize({ 100.f, 40.f });
	container.setFillColor(sf::Color::Black);
	container.setOutlineThickness(2.f);
	container.setPosition({ 20.f, 20.f });

	healthBar.setSize({ 100.f, 40.f });
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition({ 20.f, 20.f });

	scoreText.setPosition({ 20.f, 60.f });
	enemyCountText.setPosition({ 20.f, 80.f });
}

void Game::update(Player& player, unsigned int currentEnemyCount)
{
	healthBar.setSize({ 100.f * player.hp / 100.f, 40.f });

	scoreText.setString("Score: " + std::to_string(score));
	enemyCountText.setString("Enemy count: " + std::to_string(currentEnemyCount));

	if (currentEnemyCount == 0)
	{
		level++;
		maxEnemyCount = level;
		enemyCount = maxEnemyCount;
	}

	std::cout << currentEnemyCount << "\n";
}

void Game::draw(sf::RenderWindow& window)
{
	window.draw(container);
	window.draw(healthBar);
	window.draw(scoreText);
	window.draw(enemyCountText);
}
