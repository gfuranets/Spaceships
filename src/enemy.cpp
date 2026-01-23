#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "enemy.h"
#include "ship.h"
#include "player.h"

Enemy::Enemy(sf::Texture& texture, sf::RenderWindow& window, float X, float Y) :
	Ship(texture, window, X, Y), collided(false)
{
	vel = 50.f;
}

void Enemy::move(sf::Time dt) 
{
	float dirRads = alpha.asRadians(), t = dt.asSeconds();
	sf::Vector2f dir({ std::cos(dirRads), std::sin(dirRads) });
	ship.move({ dir * vel * t });
}

void Enemy::bulletCollision(std::vector<std::unique_ptr<Bullet>>& bullets)
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

void Enemy::getPlayerOrientation(Player& player)
{
	float xP = player.ship.getPosition().x, yP = player.ship.getPosition().y;
	float xE = ship.getPosition().x, yE = ship.getPosition().y;

	float orientation = std::atan2((yP - yE), (xP - xE));
	float dir = alpha.asRadians();
	float diff = orientation - dir;

	if (std::abs(diff) < 0.05f)
	{
		angularVel = sf::radians(0.f);
	}
	else
	{
		if (diff > 0) angularVel = sf::degrees(120.f);
		else angularVel = sf::degrees(-120.f);
	}
	
}

void Enemy::update(sf::RenderWindow& window, sf::Time dt, Player& player, std::vector<std::unique_ptr<Bullet>>& bullets)
{
	getPlayerOrientation(player);
	bulletCollision(bullets);
	Ship::update(window, dt);
}
