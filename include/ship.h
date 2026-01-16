#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

#include "bullet.h"

class Ship {
public:
    float vel, x, y;
    unsigned int width, height;
    sf::Angle direction, alpha, angularVel;
    sf::Sprite ship;

    explicit Ship(sf::Texture& texture, sf::RenderWindow& window, float X, float Y);

    void move(sf::Time dt);
    void rotate(sf::Time dt);
    // void exitWindow(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, sf::Time dt);
    void shoot(std::vector<Bullet*>& bullets, sf::RenderWindow& window, sf::Texture& bulletTexture) const;
    void draw(sf::RenderWindow& window);
};

#endif