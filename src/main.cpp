#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "enemy.h"
#include "bullet.h"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode({ 1200, 900 }),
				  "Spaceships",
				  sf::Style::Default,
				  sf::State::Windowed);

	sf::Clock clock;
	srand(2);

	sf::Texture playerTexture, enemyTexture, bulletTexture;
	playerTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/player.png");
	enemyTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemy.png");
	bulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/bullet.png");

	// Player player(playerTexture, windowSize, windowSize.x / 2.f, windowSize.y / 2.f);
	Player player(playerTexture, window, static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f);
	std::cout << player.x << " " << player.y << "\n";

	std::vector<Enemy*> enemies;
	for (int i = 1; i <= 3; i++)
		enemies.push_back(new Enemy(enemyTexture, window, i * 100.f, i * 150.f));

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
					std::cout << "enemy spawned, enemy count = " << enemies.size() << "\n";
					enemies.push_back(new Enemy(enemyTexture, window, X, Y));
				}
			}
		}

		// check player movement
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
			player.vel = 400.f;

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			player.vel = 0.f;
		
		sf::Time dt = clock.restart();
		// player.exitWindowCheck(windowSize);

		
		for (auto it = bullets.begin(); it != bullets.end();) {
			if ((*it)->exited(window) ||
				(*it)->collided)
			{
				delete* it;
				it = bullets.erase(it);
			}
			else 
			{
				(*it)->move(dt);
				++it;
			}
		}

		for (auto enemy = enemies.begin(); enemy != enemies.end();)
		{
			if ((*enemy)->collided)
			{
				delete* enemy;
				enemy = enemies.erase(enemy);
			}
			else ++enemy;
		}

		window.clear(sf::Color::Black);

		player.update(window, dt);

		std::cout << "x: " << player.ship.getPosition().x << " y: " << player.ship.getPosition().y << " alpha: " << player.ship.getRotation().asDegrees() << "\n";
		//std::cout << bullets.size() << "\n";
		player.draw(window);

		for (auto& enemy : enemies)
		{
			enemy->bulletCollision(bullets);
			enemy->draw(window);
		}

		for (auto& bullet : bullets)
			bullet->draw(window);

		window.display();
	}	

	for (auto& enemy : enemies) delete enemy;
	for (auto& bullet : bullets) delete bullet;
	return 0;
}