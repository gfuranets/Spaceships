#include <SFML/Graphics.hpp>

#include "bullet.h"

Bullet::Bullet(sf::Texture& texture, sf::RenderWindow &window, float X, float Y, sf::Angle angle) :
	bullet(texture), size(0.15f), x(X), y(Y), vel(600.f), alpha(angle), collided(false)
{
	sf::Vector2u bulletSize = bullet.getTexture().getSize();

	auto textureSize = texture.getSize();
	bullet.setOrigin({
		static_cast<float>(textureSize.x) / 2.f,
		static_cast<float>(textureSize.y) / 2.f
		});

	bullet.setScale({ 1.f, 1.f });
	size = bulletSize.x * bullet.getScale().x;

	bullet.setPosition({ x, y });
}

bool Bullet::exited(sf::RenderWindow& window) 
{
	float x = bullet.getPosition().x, y = bullet.getPosition().y;
	unsigned int windowWidth = window.getSize().x, windowHeight = window.getSize().y;

	if (x < -size / 2.f ||
		x > windowWidth + size / 2.f ||
		y < -size / 2.f ||
		y > windowHeight + size / 2.f)
		return true;

	return false;
}

void Bullet::move(sf::Time dt) 
{
	float angle = alpha.asRadians(), t = dt.asSeconds();

	sf::Vector2f direction({ std::cos(angle), std::sin(angle) });
	bullet.move(direction * vel * t);
}

void Bullet::draw(sf::RenderWindow &window) 
{
	window.draw(bullet);
}