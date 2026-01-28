#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "ship.h"
#include "enemy.h"
#include "config.h"

Player::Player(sf::RenderWindow& window, sf::Texture& playerTexture, float X, float Y, sf::Time timeCoolDown) :
	Ship(window, playerTexture, X, Y, timeCoolDown), direction(sf::degrees(0.f)), hp(100)
{
	vel = GameConfig::PLAYER_VELOCITY;
};

void Player::move(sf::Time dt)
{
	float dirRads = direction.asRadians(), t = dt.asSeconds();
	sf::Vector2f dir({ std::cos(dirRads), std::sin(dirRads) });
	ship.move({ dir * vel * t });
}

void Player::bulletCollision(std::vector<std::unique_ptr<Bullet>>& enemyBullets)
{
	for (auto& bullet : enemyBullets)
	{
		float xP = ship.getPosition().x, yP = ship.getPosition().y;
		float xB = bullet->bullet.getPosition().x, yB = bullet->bullet.getPosition().y;
		float bulletSize = static_cast<float>(bullet->size);

		if (abs(xP - xB) < bulletSize / 2.f &&
			abs(yP - yB) < bulletSize / 2.f)
		{
			bullet->collided = true;
			hp -= 10.f;
		}
	}
}

void Player::enemyCollision(std::vector<std::unique_ptr<Enemy>>& enemies)
{
	for (auto& enemy : enemies)
	{
		float xP = ship.getPosition().x, yP = ship.getPosition().y;
		float xE = enemy->ship.getPosition().x, yE = enemy->ship.getPosition().y;
		
		if (abs(xP - xE) <= width / 2.f &&
			abs(yP - yE) <= height / 2.f)
		{
			hp -= 20.f;
			enemy->collided = true;
		}
	}
}

void Player::update(sf::RenderWindow& window, sf::Time dt, std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Bullet>>& enemyBullets)
{
	enemyCollision(enemies);
	bulletCollision(enemyBullets);
	Ship::update(window, dt);
}