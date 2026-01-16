#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy.h"
#include "bullet.h"

void handleEnemyLogic(std::vector<Enemy*>& enemies, sf::Time dt)
{
	for (auto enemy = enemies.begin(); enemy != enemies.end();)
	{
		if ((*enemy)->collided)
		{
			delete* enemy;
			enemy = enemies.erase(enemy);
		}
		else ++enemy;
	}
}

void handleBulletLogic(std::vector<Bullet*>& bullets, sf::RenderWindow& window, sf::Time dt)
{
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		if ((*bullet)->exited(window) ||
			(*bullet)->collided)
		{
			delete* bullet;
			bullet = bullets.erase(bullet);
		}
		else
		{
			(*bullet)->move(dt);
			++bullet;
		}
	}
}

void clearObjects(std::vector<Enemy*>& enemies, std::vector<Bullet*>& bullets)
{
	for (auto& enemy : enemies) delete enemy;
	for (auto& bullet : bullets) delete bullet;
}