#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "gameLogic.h"

int main() 
{
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 900 }),
					"Spaceships",
					sf::Style::Default,
					sf::State::Windowed);

	sf::Clock clock;
	srand(2);

	// TEXTURES
	sf::Texture playerTexture, enemyTexture, playerBulletTexture, enemyBulletTexture;
	playerTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/player.png");
	enemyTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemy.png");
	playerBulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/playerBullet.png");
	enemyBulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemyBullet.png");

	// INITIALIZING GAME ENTITIES
	Player player(window, playerTexture, static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f);
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Bullet>> playerBullets;
	std::vector<std::unique_ptr<Bullet>> enemyBullets;

	// GAME LOOP
	while (window.isOpen())
	{
		// EVENT LOOP
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (const auto* pressedKey = event->getIf<sf::Event::KeyPressed>())
			{
				if (pressedKey->scancode == sf::Keyboard::Scancode::Escape)
					window.close();

				if (pressedKey->scancode == sf::Keyboard::Scancode::Space) 
					player.shoot(window, playerBullets, playerBulletTexture);
			}
		}

		// refresh enemies
		while (enemies.size() < 5)
		{
			float X = static_cast<float>(rand() % window.getSize().x), Y = static_cast<float>(rand() % window.getSize().y);
			enemies.push_back(std::make_unique<Enemy>(window, enemyTexture, X, Y));
		}

		// PLAYER MOVEMENT LOGIC
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
			player.angularVel = sf::degrees(-180.f);
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player.angularVel = sf::degrees(180.f);

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player.angularVel = sf::degrees(0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			player.direction = player.ship.getRotation();	

		// GAME LOGIC
		sf::Time dt = clock.restart();

		player.update(window, dt);
		enemyUpdate(window, dt, player, enemies, playerBullets, enemyBullets, enemyBulletTexture);
		bulletUpdate(window, dt, playerBullets);
		bulletUpdate(window, dt, enemyBullets);
		
		// DISPLAYING

		window.clear(sf::Color::Black);	
		// std::cout << "x: " << player.ship.getPosition().x << " y: " << player.ship.getPosition().y << " alpha: " << player.ship.getRotation().asDegrees() << "\n";
		
		player.draw(window);
		drawEntities(window, enemies, playerBullets, enemyBullets);

		// std::cout << player.width << " " << player.height << "\n";

		// std::cout << "enemy count: " << enemies.size() << "\n";

		window.display();
	}	

	return 0;
}
