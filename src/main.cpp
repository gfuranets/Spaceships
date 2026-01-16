#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "updateFunctions.h"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 900 }),
				  "Spaceships",
				  sf::Style::Default,
				  sf::State::Windowed);

	sf::Clock clock;
	srand(2);

	// TEXTURES
	sf::Texture playerTexture, enemyTexture, bulletTexture;
	playerTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/player.png");
	enemyTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemy.png");
	bulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/bullet.png");

	// GAME OBJECTS
	Player player(playerTexture, window, static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f);
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;

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

				if (pressedKey->scancode == sf::Keyboard::Scancode::Space) {
					player.shoot(bullets, window, bulletTexture);
				}

				if (pressedKey->scancode == sf::Keyboard::Scancode::C)
				{
					float X = static_cast<float>(rand() % window.getSize().x), Y = static_cast<float>(rand() % window.getSize().y);
					enemies.push_back(new Enemy(enemyTexture, window, X, Y));
				}
			}
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
		handleEnemyLogic(enemies, dt);
		handleBulletLogic(bullets, window, dt);

		// DISPLAYING

		window.clear(sf::Color::Black);	
		//std::cout << "x: " << player.ship.getPosition().x << " y: " << player.ship.getPosition().y << " alpha: " << player.ship.getRotation().asDegrees() << "\n";
		//std::cout << bullets.size() << "\n";
		
		player.draw(window);

		for (auto& enemy : enemies)
			enemy->draw(window);

		for (auto& bullet : bullets)
			bullet->draw(window);

		// std::cout << "enemy count: " << enemies.size() << "\n";

		window.display();
	}	

	clearObjects(enemies, bullets);
	return 0;
}