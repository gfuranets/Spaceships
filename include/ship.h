#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

#include "bullet.h"

class Ship 
{
public:
    float vel, width, height;
    sf::Angle alpha, angularVel;
    sf::Sprite ship;

    explicit Ship(sf::RenderWindow& window, sf::Texture& texture, float X, float Y);

    virtual void move(sf::Time dt) = 0;
    virtual ~Ship() = default;

    void rotate(sf::Time dt);
    void exitWindow(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, sf::Time dt);

    void shoot(sf::RenderWindow& window, std::vector<std::unique_ptr<Bullet>>& bullets, sf::Texture& bulletTexture, float bulletVel) const;
    void draw(sf::RenderWindow& window);
};

#endif