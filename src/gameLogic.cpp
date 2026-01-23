#include <SFML/Graphics.hpp>
#include <vector>

#include "gameLogic.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"

void enemyUpdate(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& bullets, Player& player, sf::RenderWindow& window, sf::Time dt)
{
	for (auto enemy = enemies.begin(); enemy != enemies.end();)
	{
		if ((*enemy)->collided)
		{
			// no need for delete with std::unique_ptr
			enemy = enemies.erase(enemy);
		}
		else
		{
			(*enemy)->update(window, dt, player, bullets);
			++enemy;
		}
	}
}

void bulletUpdate(sf::RenderWindow& window, sf::Time dt, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	for (auto bullet = bullets.begin(); bullet != bullets.end();)
	{
		if ((*bullet)->exited(window) ||
			(*bullet)->collided)
		{
			bullet = bullets.erase(bullet);
		}
		else
		{
			(*bullet)->move(dt);
			++bullet;
		}
	}
}

void drawEntities(sf::RenderWindow& window, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	for (auto& enemy : enemies) enemy->draw(window);
	for (auto& bullet : bullets) bullet->draw(window);
}
