#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "enemy.h"
#include "ship.h"
#include "player.h"

Enemy::Enemy(sf::RenderWindow& window, sf::Texture& texture, float X, float Y) :
	Ship(window, texture, X, Y), collided(false)
{
	vel = 50.f;
}

void Enemy::move(sf::Time dt) 
{
	float dirRads = alpha.asRadians(), t = dt.asSeconds();
	sf::Vector2f dir({ std::cos(dirRads), std::sin(dirRads) });
	ship.move({ dir * vel * t });
}

void Enemy::bulletCollision(std::vector<std::unique_ptr<Bullet>>& playerBullets)
{
	for (auto& bullet : playerBullets)
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

void Enemy::getPlayerOrientation(sf::RenderWindow& window, Player& player, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture)
{
	float xP = player.ship.getPosition().x, yP = player.ship.getPosition().y;
	float xE = ship.getPosition().x, yE = ship.getPosition().y;

	float orientation = std::atan2((yP - yE), (xP - xE));
	float dir = alpha.asRadians();
	float diff = orientation - dir;

	float pi = sf::degrees(180.f).asRadians();
	while (diff < pi) diff += 2.f * pi;
	while (diff > pi) diff -= 2.f * pi;

	if (std::abs(diff) < 0.05f)
	{
		angularVel = sf::radians(0.f);
		shoot(window, enemyBullets, enemyBulletTexture, ENEMY_BULLET_VEL);
	}
	else
	{
		if (diff > 0) angularVel = sf::degrees(25.f);
		else angularVel = sf::degrees(-25.f);
	}
	
}

void Enemy::update(sf::RenderWindow& window, sf::Time dt, Player& player, std::vector<std::unique_ptr<Bullet>>& playerBullets, std::vector<std::unique_ptr<Bullet>>& enemyBullets, sf::Texture& enemyBulletTexture)
{
	getPlayerOrientation(window, player, enemyBullets, enemyBulletTexture);
	bulletCollision(playerBullets);
	Ship::update(window, dt);
}
