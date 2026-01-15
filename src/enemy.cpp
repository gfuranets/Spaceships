#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy.h"
#include "ship.h"

Enemy::Enemy(sf::Texture& texture, sf::RenderWindow& window, float X, float Y) :
	Ship(texture, window, X, Y), collided(false) 
{ }

/*
void Enemy::bulletCollision(std::vector<Bullet*>& bullets)
{
	for (auto& bullet : bullets)
	{
		if (ship.getGlobalBounds().findIntersection(bullet->bullet.getGlobalBounds()))
		{
			bullet->collided = true;
			collided = true;
		}
	}
}
*/

void Enemy::bulletCollision(std::vector<Bullet*>& bullets)
{
	for (auto& bullet : bullets)
	{
		float xE = ship.getPosition().x, yE = ship.getPosition().y;
		float xB = bullet->bullet.getPosition().x, yB = bullet->bullet.getPosition().y;
		float bulletSize = static_cast<float>(bullet->size);

		if (abs(xE - xB) < bulletSize / 2.f &&
			abs(yE - yB) < bulletSize / 2.f)
		{
			bullet->collided = true;
			collided = true;
		}
	}
}
