#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
	float x, y, vel, size;
	bool collided;
	sf::Angle alpha;
	sf::Sprite bullet;

	Bullet(sf::Texture& texture, sf::RenderWindow &window, float X, float Y, sf::Angle angle, float velocity);

	bool exited(sf::RenderWindow& window);
	void move(sf::Time dt);
	void draw(sf::RenderWindow& window);
};

#endif
