#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "gameLogic.h"
#include "config.h" 
#include "game.h"

int main() 
{
	sf::RenderWindow window;
	window.create(sf::VideoMode({ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }),
				  "Spaceships",
				  sf::Style::Default,
				  sf::State::Windowed);

	sf::Clock clock;
	srand(2);

	// TEXTURES AND FONT
	sf::Texture playerTexture, enemyTexture, playerBulletTexture, enemyBulletTexture;
	playerTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/player.png");
	enemyTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemy.png");
	playerBulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/playerBullet.png");
	enemyBulletTexture.loadFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/enemyBullet.png");

	sf::Font font;
	font.openFromFile("C:/Users/furen/OneDrive/Dators/Programming/Projects/Spaceships/assets/fontArena.ttf");

	// INITIALIZING GAME ENTITIES
	Game game(font);
	Player player(window, playerTexture, static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f, GameConfig::PLAYER_TIME_COOLDOWN);
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
					player.shoot(window, playerBullets, playerBulletTexture, GameConfig::PLAYER_BULLET_VELOCITY);
			}
		}

		if (player.hp <= 0.f) window.close();

		// PLAYER MOVEMENT LOGIC
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			player.angularVel = -GameConfig::PLAYER_ANGULAR_VEL;
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player.angularVel = GameConfig::PLAYER_ANGULAR_VEL;

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

		player.update(window, dt, enemies, enemyBullets);
		enemyUpdate(window, dt, player, enemies, playerBullets, enemyBullets, enemyBulletTexture, game);
		bulletUpdate(window, dt, playerBullets);
		bulletUpdate(window, dt, enemyBullets);
		game.update(player, enemies.size());

		// refresh enemies
		if (enemies.size() == 0)
		{
			while (enemies.size() <= game.maxEnemyCount)
			{
				float X = static_cast<float>(rand() % window.getSize().x), Y = static_cast<float>(rand() % window.getSize().y);
				enemies.push_back(std::make_unique<Enemy>(window, enemyTexture, X, Y, GameConfig::ENEMY_TIME_COOLDOWN));
			}
		}
		
		// DISPLAYING
		window.clear(sf::Color::Black);	
		
		player.draw(window);
		drawEntities(window, enemies, playerBullets, enemyBullets);
		game.draw(window);

		window.display();
	}	

	return 0;
}
